#include "precomp.h" // include (only) this in every .cpp file

#define FRAMECOUNT	64

Rasterizer rasterizer;
Camera camera;
vec3 position;
SGNode* cube;
Surface half( 256, 212 ); // msx screen size
Surface img( 144, 144 );

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	// initialize rasterizer
	rasterizer.Init( &half );
	// setup camera (note: in ogl/glm, z for 'far' is -inf)
	position = vec3( 0, 0, 0 );
	camera.SetPosition( position );
	camera.LookAt( vec3( 0, 0, 1 ) );
	// initialize scene
	cube = rasterizer.scene->Add( "assets/cube.obj" );
	half.Clear( 0x191919 );
}

// -----------------------------------------------------------
// Main application tick function
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{
	static float a = 0;
	static int frameIdx = 0;
	static bool done = false;
	if (!done)
	{
		// render a frame and store it
		cube->localTransform = mat4::rotatey( a ) * mat4::rotatex( 0.4f ) * mat4::translate( -0.01f, 0, -8.1 );
		a += PI / (FRAMECOUNT * 2);
		if (a > 0.5f * PI) 
		{
			frameIdx = 0, done = true; 
			CreateMSXData();
		}
		else
		{
			screen->Clear( 0 );
		#if 0
			for (int x = 10; x < 22; x++) for (int y = 8; y < 20; y++)
				half.Bar( x * 8, y * 8, x * 8 + 7, y * 8 + 7, (x + y) & 1 ? 0 : 0x090909 );
		#else
			half.Bar( 80, 64, 21 * 8 + 7, 19 * 8 + 7, 0 );
		#endif
			rasterizer.Render( camera );
			half.CopyTo( &img, -80, -64 );
			Process( frameIdx++, img );
		}
	}
	else
	{
		// replay
		Frame& f = frames[frameIdx];
		for( int y = 0; y < 12; y++ ) for( int x = 0; x < 12; x++ )
		{
			uint tileIdx = f.unique[f.tile[x + y * 12]];
			Tile& t = tiles[tileIdx];
			for( int v = 0; v < 8; v++ ) for( int u = 0; u < 8; u++ )
				half.Plot( x * 8 + u + 80, y * 8 + v + 64, t.buffer[u + v * 8] );
		}
		if (++frameIdx == frames.size()) frameIdx = 0;
	}
	// display the frame at twice the size
	uint* s = half.GetBuffer();
	for (int y = 0; y < 212; y++)
	{
		uint* d = screen->GetBuffer() + y * screen->GetWidth() * 2;
		for (int x = 0; x < 256; x++, d += 2)
			d[0] = d[1] = d[512] = d[513] = *s++;
	}
	// limit frame rate to 30fps
	Sleep( 33 );
}

// -----------------------------------------------------------
// Process one animation frame into tiles
// -----------------------------------------------------------
void Game::Process( const int frameIdx, Surface& img )
{
	Frame frame;
	for (int y = 0; y < 12; y++) for (int x = 0; x < 12; x++)
	{
		// grab a tile
		Tile t;
		uint* s = img.GetBuffer() + x * 8 + y * 8 * 144;
		for (int v = 0; v < 8; v++) for (int u = 0; u < 8; u++) t.buffer[u + v * 8] = s[u + v * 144];
		// see if it is new
		bool unique = true;
		size_t tileIdx = tiles.size();
		for( size_t i = 0; i < tiles.size(); i++ ) if (t.Equals( tiles[i] )) { tileIdx = i, unique = false; break; }
		if (unique) 
		{
			t.CountColors();
			t.CalcMSXColors();
			tiles.push_back( t );
		}
		frame.tile[x + y * 12] = (uint)tileIdx;
	}
	frame.CountUniqueTiles( frameIdx, tiles );
	frames.push_back( frame );
	printf( "frame %03i: %i unique tiles\n", frameIdx, frame.uniques );
}

void Game::CreateMSXData()
{
	// report
	printf( "unique tiles: %i\n", (int)tiles.size() );
	int totalFrameUniques = 0;
	for (int j = 0; j < FRAMECOUNT; j++) totalFrameUniques += frames[j].uniques;
	printf( "average unique per frame: %4.1f\n", (float)totalFrameUniques / FRAMECOUNT );
	// emit tile data
	FILE* f = fopen( "tiles.h", "w" );
	fprintf( f, "// const u16 tileCount = %i;\n", tiles.size() );
	fprintf( f, "__at( 0x0200 ) const u8 tile[] = {\n" );
	for( int c = 0, i = 0; i < tiles.size(); i++ )
	{
		for( int j = 0; j < 8; j++ ) 
		{
			fprintf( f, "%i,", (int)tiles[i].msxdata[j] );
		}
		if (++c == 4) { fprintf( f, "\n" ); c = 0; }
	}
	fprintf( f, "};" );
	fclose( f );
	// emit frames
	f = fopen( "frames.h", "w" );
	fprintf( f, "// const u16 frameCount = %i;\n", FRAMECOUNT );
	fprintf( f, "const u8 frame[] = {\n" );
	for( int i = 0; i < FRAMECOUNT; i++ )
	{
		for( int p = 0; p < 144; p++ ) 
		{
			fprintf( f, "%i,", frames[i].tile[p] );
			if (p % 24 == 23) fprintf( f, "\n" );
		}
		// total: 64 * 144 bytes
	}
	fprintf( f, "};\n" );
	// emit unique offsets
	fprintf( f, "const u16 offset[] = {\n" );
	int offset = 0;
	for (int i = 0; i < FRAMECOUNT; i++)
	{
		fprintf( f, "%i,", offset );
		offset += frames[i].uniques;
		if ((i & 15) == 15) fprintf( f, "\n" );
		// total: 128 bytes
	}
	fprintf( f, "%i };\n", offset );
	// emit unique array
	fprintf( f, "const u16 unique[] = {\n" );
	for (int i = 0; i < FRAMECOUNT; i++)
	{
		int s[6] = { 0, 0, 0, 0, 0, 0 };
		for( int j = 0; j < frames[i].uniques; j++ )
		{
			uint u = frames[i].unique[j];
			uint slice = tiles[u].slice;
			u = (u << 3) + slice;
			fprintf( f, "%i,", u );
			s[slice]++;
		}
		fprintf( f, "\n" );
		printf( "frame %i, slices: %i %i %i %i %i %i\n", i, s[0], s[1], s[2], s[3], s[4], s[5] );
		// total: 51 * 64 = 3264 bytes, sum: ~12.5KB
	}
	fprintf( f, "};\n" );
	// emit sprite offsets
	fprintf( f, "const u16 sproff[] = {\n" );
	offset = 0;
	for (int i = 0; i < FRAMECOUNT; i++)
	{
		fprintf( f, "%i,", offset );
		for( int j = 0; j < 144; j++ )
		{
			uint u = frames[i].tile[j];
			Tile& t = tiles[frames[i].unique[u]];
			if (t.sprcol != 0) offset++;
		}
	}
	fprintf( f, "%i };\n", offset );
	// emit sprite tiles
	fprintf( f, "const u8 sprpat[] = {\n" );
	for (int i = 0; i < FRAMECOUNT; i++)
	{
		for (int j = 0; j < 144; j++)
		{
			uint u = frames[i].tile[j];
			Tile& t = tiles[frames[i].unique[u]];
			if (t.sprcol != 0) for( int y = 0; y < 8; y++ ) fprintf( f, "%i,", t.sprdata[y] );
		}
	}
	fprintf( f, "};\n" );
	// emit sprite attributes
	fprintf( f, "u8 spratr[] = {\n" );
	for (int i = 0; i < FRAMECOUNT; i++)
	{
		int idx = 0;
		for (int j = 0; j < 144; j++)
		{
			uint u = frames[i].tile[j];
			Tile& t = tiles[frames[i].unique[u]];
			if (t.sprcol != 0) fprintf( f, "%i,%i,%i,%i,", (j / 12) * 8 + (63 - 16), (j % 12) * 8 + 80, idx++, t.sprcol );
		}
		if (idx > 0) fprintf( f, "\n" );
	}
	fprintf( f, "};" );
	fclose( f );
}