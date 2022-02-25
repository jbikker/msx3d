#include "msxgl.h"
#include "myproj.h"
#include "frames.h"
#include "tiles.h"
#include "customasm.h"

static bool vsync = false;
static i8 pal1[32], pal2[32];
static u8 base = 0;
static u8 cidx[64], pile[6], prevCount = 0;
static u8 lbuf[12 * 12], *line;

void vsynchook() { vsync = true; }
void waitvsync() { while (!vsync); vsync = false; }
void VDP_InterruptHandler() { vsynchook(); }

void init()
{
	VDP_SetMode( VDP_MODE_SCREEN1 /* aka VDP_MODE_GRAPHIC1 */ );
	// in this screen mode we have:
	// 0000h: sprite patterns
	// 1000h: sprite attributes
	// 0800h: pattern table; the character set: 8 bytes per character.
	// 1400h: name table; the 'map'.
	// 2000h: color table; colors of 32 groups of 8 chars.
	VDP_EnableVBlank( true );
	VDP_RegWrite( 7, 1 /* border: black */ );
	Bios_SetHookCallback( H_TIMI, vsynchook );
	VDP_FillVRAM_16K( 0, 0, 16384 ); // Clear 16KB VRAM
	// prepare two 'palletes'
	for (u8 i = 0; i < 3; i++)
	{
		pal1[i + 0] = pal1[i + 16] = (COLOR_MEDIUM_RED << 4) + COLOR_BLACK;				// slice = 0, red/black
		pal1[i + 3] = pal1[i + 19] = (COLOR_MEDIUM_GREEN << 4) + COLOR_BLACK;			// slice = 1, green/black
		pal1[i + 6] = pal1[i + 22] = (COLOR_LIGHT_BLUE << 4) + COLOR_BLACK;				// slice = 2, blue/black
		pal1[i + 9] = pal1[i + 25] = (COLOR_MEDIUM_GREEN << 4) + COLOR_MEDIUM_RED;		// slice = 3, green/red
		pal2[i + 0] = pal2[i + 16] = (COLOR_MEDIUM_GREEN << 4) + COLOR_BLACK;			// slice = 0, red/black
		pal2[i + 3] = pal2[i + 19] = (COLOR_MEDIUM_RED << 4) + COLOR_BLACK;				// slice = 1, green/black
		pal2[i + 6] = pal2[i + 22] = (COLOR_LIGHT_BLUE << 4) + COLOR_BLACK;				// slice = 2, blue/black
		pal2[i + 9] = pal2[i + 25] = (COLOR_MEDIUM_RED << 4) + COLOR_MEDIUM_GREEN;		// slice = 3, green/red
	}
	for (u8 i = 0; i < 2; i++)
	{
		pal1[i + 12] = pal1[i + 28] = (COLOR_LIGHT_BLUE << 4) + COLOR_MEDIUM_RED;		// slice = 4, blue/red
		pal1[i + 14] = pal1[i + 30] = (COLOR_MEDIUM_GREEN << 4) + COLOR_LIGHT_BLUE;		// slice = 5, green/blue
		pal2[i + 12] = pal2[i + 28] = (COLOR_LIGHT_BLUE << 4) + COLOR_MEDIUM_GREEN;		// slice = 4, blue/red
		pal2[i + 14] = pal2[i + 30] = (COLOR_MEDIUM_RED << 4) + COLOR_LIGHT_BLUE;		// slice = 5, green/blue
	}
	pal1[31] = pal2[31] = (COLOR_BLACK << 4) + COLOR_BLACK;
	VDP_FillVRAM_16K( 255, 0x1400, 32 * 24 );
}

void buildFrame( u8 f )
{
	// set color map
	if (f < 2)
	{
		if (base == 0) VDP_WriteVRAM_16K( pal1, 0x2000, 16 );
		else VDP_WriteVRAM_16K( pal1 + 16, 0x2000 + 16, 16 );
	}
	if (f == 64 || f == 65)
	{
		if (base == 0) VDP_WriteVRAM_16K( pal2, 0x2000, 16 );
		else VDP_WriteVRAM_16K( pal2 + 16, 0x2000 + 16, 16 );
	}
	f &= 63;
	// build characters
	u16* uni = unique + offset[f];
	const u8 unis = offset[f + 1] - offset[f];
	pile[0] = base, pile[1] = base + 24, pile[2] = base + 48, pile[3] = base + 72, pile[4] = base + 96, pile[5] = base + 112;
	for (u8 i = 0; i < unis; i++)
	{
		const u16 tileIdx = uni[i];
		const u8 c = pile[tileIdx & 7]++;
		cidx[i] = c;
		VDP_WriteVRAM_16K_8( tile + (tileIdx & 0xfff8), 0x4800 + (c << 3) );
	}
	// prep character image
	u16 idx = (f << 7) + (f << 4), o = 0x540A + (6 << 5);
	line = lbuf;
	for (u8 y = 12; y; --y, o += 32, idx += 12, line += 12 )
	{
		line[0] = cidx[frame[idx + 0]], line[1] = cidx[frame[idx + 1]];
		line[2] = cidx[frame[idx + 2]], line[3] = cidx[frame[idx + 3]];
		line[4] = cidx[frame[idx + 4]], line[5] = cidx[frame[idx + 5]];
		line[6] = cidx[frame[idx + 6]], line[7] = cidx[frame[idx + 7]];
		line[8] = cidx[frame[idx + 8]], line[9] = cidx[frame[idx + 9]];
		line[10] = cidx[frame[idx + 10]], line[11] = cidx[frame[idx + 11]];
	}
	// final precalculations
	const u8 sprtiles = sproff[f + 1] - sproff[f];
	// ^^^ ======================= ABOVE THIS LINE: STUFF THAT ISN'T IMMEDIATELY VISIBLE
	waitvsync();
	// vvv ======================= BELOW THIS LINE: STUFF THAT CHANGES THE DISPLAY
	// write sprite patterns
	for( u8 i = 0; i < sprtiles; i++ )
	{
		VDP_WriteVRAM_16K_8( sprpat + ((sproff[f] + i) << 3), 0x4000 + (i << 3) );
		VDP_WriteVRAM_16K_4( spratr + ((sproff[f] + i) << 2), 0x5000 + (i << 2) );
	}
	// build character image
	VDP_WriteVRAM_16K_12x12( lbuf ); 
	// clear unused sprites, if any
	if (prevCount > sprtiles)
	{
		VDP_FillVRAM_16K( 0, 0x1000 + (sprtiles << 2), (prevCount - sprtiles) << 2 );
		VDP_FillVRAM_16K( 0, sprtiles << 3, (prevCount - sprtiles) << 3 );
	}
	//     ======================= AT THIS POINT: DRAWING TO DISPLAY HAS COMPLETED
	prevCount = sprtiles;
	// flip red/green for second half of cycle
	u8* a = spratr + (sproff[f] << 2) + 3;
	for (u8 i = 0; i < sprtiles; i++, a += 4) if (*a == 8) *a = 2; else if (*a == 2) *a = 8;
	base ^= 128;
}

void main()
{
	init();
	/* sizeof( tile ) : 11680, sizeof( frame ) : 9216, sizeof( offset ) : 128,
	   sizeof( unique ) : 6526, total: 27550 */
	i8 w = 0;
	while (!Keyboard_IsKeyPressed( KEY_ESC ))
	{
		buildFrame( w );
		// for( u16 i = 0; i < 5000; i++ ) VDP_WriteVRAM_16K( &i, 0xFF00, 1 );
		w = (w + 1) & 127;
	}
	Bios_Exit( 0 );
}