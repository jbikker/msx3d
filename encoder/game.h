#pragma once

namespace Tmpl8
{

class Tile
{
public:
	bool Equals( Tile& t )
	{
		for( int i = 0; i < 64; i++ ) if (t.buffer[i] != buffer[i]) return false;
		return true;
	}
	void CountColors()
	{
		bool c0 = false, c1 = false, c2 = false, c3 = false;
		for( int i = 0; i < 64; i++ )
		{
			c0 |= (buffer[i] & 0xffffff) == 0x090909 || buffer[i] == 0;
			c1 |= (buffer[i] & 0xffffff) == 0xff0000;
			c2 |= (buffer[i] & 0xffffff) == 0x00ff00;
			c3 |= (buffer[i] & 0xffffff) == 0x0000ff;
		}
		colors = (c0 ? 1 : 0) + (c1 ? 1 : 0) + (c2 ? 1 : 0) + (c3 ? 1 : 0);
		hasColor[0] = c0;
		hasColor[1] = c1;
		hasColor[2] = c2;
		hasColor[3] = c3;
	}
	void CalcMSXColors()
	{
		uint p1, p2, p3 = 0x999999;
		slice = 999;
		if (hasColor[1])
		{
			if (hasColor[0]) slice = 0; else if (hasColor[3]) slice = 4; else if (colors == 1) slice = 3;
		}
		if (slice == 999 && hasColor[2])
		{
			if (hasColor[0]) slice = 1; else if (hasColor[1]) slice = 3; else if (colors == 1) slice = 3;
		}
		if (slice == 999 && hasColor[3])
		{
			if (hasColor[2]) slice = 5; else if (hasColor[0]) slice = 2; else if (colors == 1) slice = 2;
		}
		if (slice == 999) if (colors == 1) slice = 2;
		if (slice == 0) p1 = 0xff0000, p2 = 0x000000;
		if (slice == 1) p1 = 0x00ff00, p2 = 0x000000;
		if (slice == 2) p1 = 0x0000ff, p2 = 0x000000;
		if (slice == 3) p1 = 0x00ff00, p2 = 0xff0000;
		if (slice == 4) p1 = 0x0000ff, p2 = 0xff0000;
		if (slice == 5) p1 = 0x00ff00, p2 = 0x0000ff;
		for( int y = 0; y < 8; y++ )
		{
			msxdata[y] = 0;
			for( int x = 0; x < 8; x++ )
			{
				uint p = buffer[y * 8 + x];
				if (p == p1) msxdata[y] += 1 << (7 - x);
				else if (p != p2) p3 = p;
			}
		}
		if (p3 != 0x999999)
		{
			// third color; add sprite
			for (int y = 0; y < 8; y++)
			{
				if (p3 == 0x000000) sprcol = 1; // COLOR_BLACK
				if (p3 == 0xff0000) sprcol = 8; // COLOR_MEDIUM_RED
				if (p3 == 0x00ff00) sprcol = 2; // COLOR_MEDIUM_GREEN
				if (p3 == 0x0000ff) sprcol = 5; // COLOR_LIGHT_BLUE
				sprdata[y] = 0;
				for (int x = 0; x < 8; x++)
					if (buffer[y * 8 + x] == p3) sprdata[y] += 1 << (7 - x);
			}
		}
		else sprcol = 0;
	}
	uint buffer[64], colors = 0, seen = 999999, col1, col2, slice;
	bool hasColor[4];
	uchar msxdata[8], sprdata[8], sprcol;
};

class Frame
{
public:
	uint tile[144];
	uint unique[144], uniques = 0;
	void CountUniqueTiles( int frameIdx, vector<Tile>& tiles )
	{
		for (int i = 0; i < 144; i++)
		{
			bool seenBefore = tiles[tile[i]].seen == frameIdx;
			tiles[tile[i]].seen = frameIdx;
			if (!seenBefore) 
			{
				unique[uniques] = tile[i], tile[i] = uniques++;
			}
			else
			{
				for( uint j = 0; j < uniques; j++ ) if (unique[j] == tile[i]) { tile[i] = j; break; }
			}
		}
	}
};

// Storage on MSX, BASICS:
// - Use fixed character colors in the color map.
// - Per frame, set up to 64 char patterns to new values: 64*8=512 bytes.
// - Per frame, place 12x12 chars in a 32x12 buffer and copy to vdp: 284 bytes.
// - Storage per frame: 144 tile indices -> 288 bytes, ~36KB for 128 frames.
//             smaller: 144 8-bit indices in ~51 element 'unique' array: ~250 bytes, 16KB
//        even smaller: 144 6-bit indices in ~51 element 'unique' array: ~212 bytes, 13.5KB
// - Tile storage: 1460 unique tiles -> 11.5KB
// - Store chars in 'unique' in the correct color slice;
//   for 4 colors RGBY we have 6 slices: RG,RB,RY,GB,GY,BY.
//   encode the slice nr in 3 bits (leaving 13 for tile index: 8192 max).
//   (for 3 colors RGB we would get: RG,RB,GB, so 16384 tiles max)
// ADVANCED:
// 1. Unconditionally add the four solid coloured tiles to each frame, on indices 0..3.
//    These do not have to be synced after frame 0, reducing most (all?) frames by 4 chars.
// 2. Try to construct tiles from existing tiles with a 1 or 2 bit shift to the left.
//    Also try if the existing tile could be made by shifting the new one to the left.
//    This should roughly halve tile storage requirements.
// 3. Tiles can also be equal if they have the same pattern, but in a different slice.

class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown() {}
	void Tick( float deltaTime );
	void Process( const int frameIdx, Surface& frame );
	void CreateMSXData();
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
	vector<Tile> tiles;
	vector<Frame> frames;
};

}; // namespace Tmpl8