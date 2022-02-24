#include "msxgl.h"
#include "myproj.h"
#include "frames.h"
#include "tiles.h"

static bool vsync = false;
static i8 pal1[32], pal2[32];
static u8 base = 0;
static u8 cidx[64], line[12], pile[6], prevCount = 0;
static u16 lbuf[6 * 12], *line16;

void vsynchook() { vsync = true; }
void waitvsync() { while (!vsync); vsync = false; }
void VDP_InterruptHandler() { vsynchook(); }

void VDP_WriteVRAM_16K_4( const u8* src, u16 dest ) __sdcccall( 0 )
{
	src, dest;
	__asm
		push	ix
		ld		ix, #0
		add		ix, sp
		ld		a, 6(ix)
		di
		out( 0x99 ), a
		ld		a, 7(ix)
		ei
		out( 0x99 ), a
		ld		l, 4(ix)
		ld		h, 5(ix)
		ld		c, #0x98
		outi
		outi
		outi
		outi
		pop		ix
		__endasm;
}

void VDP_WriteVRAM_16K_8( const u8* src, u16 dest ) __sdcccall( 0 )
{
	src, dest;
	__asm
		push	ix
		ld		ix, #0
		add		ix, sp
		ld		a, 6(ix)
		di
		out( 0x99 ), a
		ld		a, 7(ix)
		ei
		out( 0x99 ), a
		ld		l, 4(ix)
		ld		h, 5(ix)
		ld		c, #0x98
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		pop		ix
	__endasm;
}

void VDP_WriteVRAM_16K_12( const u8* src, u16 dest ) __sdcccall( 0 )
{
	src, dest;
	__asm
		push	ix
		ld		ix, #0
		add		ix, sp
		ld		a, 6(ix)
		di
		out( 0x99 ), a
		ld		a, 7(ix)
		ei
		out( 0x99 ), a
		ld		l, 4(ix)
		ld		h, 5(ix)
		ld		c, #0x98
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		pop		ix
		__endasm;
}

void VDP_WriteVRAM_16K_12x12( const u8* src ) __sdcccall( 0 )
{
	src; // , dest = 0x54CA;
	__asm
		push	ix
		ld		ix, #0
		add		ix, sp
		ld		a, #0xCA
		di
		out( 0x99 ), a
		ld		a, #0x54
		ei
		out( 0x99 ), a
		ld		l, 4(ix)
		ld		h, 5(ix)
		ld		c, #0x98
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0xEA
		di
		out( 0x99 ), a
		ld		a, #0x54
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0x0A
		di
		out( 0x99 ), a
		ld		a, #0x55
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0x2A
		di
		out( 0x99 ), a
		ld		a, #0x55
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0x4A
		di
		out( 0x99 ), a
		ld		a, #0x55
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0x6A
		di
		out( 0x99 ), a
		ld		a, #0x55
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0x8A
		di
		out( 0x99 ), a
		ld		a, #0x55
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0xAA
		di
		out( 0x99 ), a
		ld		a, #0x55
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0xCA
		di
		out( 0x99 ), a
		ld		a, #0x55
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0xEA
		di
		out( 0x99 ), a
		ld		a, #0x55
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0x0A
		di
		out( 0x99 ), a
		ld		a, #0x56
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		ld		a, #0x2A
		di
		out( 0x99 ), a
		ld		a, #0x56
		ei
		out( 0x99 ), a
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		pop		ix
	__endasm;
}

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

void buildFrame( u16 f )
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
	for (i8 i = 0; i < unis; i++)
	{
		const u16 tileIdx = uni[i];
		const u8 c = pile[tileIdx & 7]++;
		cidx[i] = c;
		VDP_WriteVRAM_16K_8( tile + (tileIdx & 0xfff8), 0x4800 + (c << 3) );
	}
	// prep character image
	u16 idx = (f << 7) + (f << 4), o = 0x540A + (6 << 5);
	line16 = lbuf;
	for (u8 y = 12; y; --y, o += 32, idx += 12, line16 += 6 )
	{
		line16[0] = cidx[frame[idx + 0]] + (cidx[frame[idx + 1]] << 8);
		line16[1] = cidx[frame[idx + 2]] + (cidx[frame[idx + 3]] << 8);
		line16[2] = cidx[frame[idx + 4]] + (cidx[frame[idx + 5]] << 8);
		line16[3] = cidx[frame[idx + 6]] + (cidx[frame[idx + 7]] << 8);
		line16[4] = cidx[frame[idx + 8]] + (cidx[frame[idx + 9]] << 8);
		line16[5] = cidx[frame[idx + 10]] + (cidx[frame[idx + 11]] << 8);
	}
	// final precalculations
	const u16 sprtiles = sproff[f + 1] - sproff[f];
	line16 = lbuf, o = 0x540A + (6 << 5);
	// ^^^ ======================= ABOVE THIS LINE: STUFF THAT ISN'T IMMEDIATELY VISIBLE
	waitvsync();
	// vvv ======================= BELOW THIS LINE: STUFF THAT CHANGES THE DISPLAY
	// write sprite patterns
	for( i16 i = 0; i < sprtiles; i++ )
	{
		VDP_WriteVRAM_16K_8( sprpat + ((sproff[f] + i) << 3), 0x4000 + (i << 3) );
		VDP_WriteVRAM_16K_4( spratr + ((sproff[f] + i) << 2), 0x5000 + (i << 2) );
	}
	// build character image
#if 1
	VDP_WriteVRAM_16K_12x12( line16 ); 
#else
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o ); o += 32, line16 += 6;
	VDP_WriteVRAM_16K_12( line16, o );
#endif
	// clear unused sprites, if any
	if (prevCount > sprtiles)
	{
		VDP_FillVRAM_16K( 0, 0x1000 + (sprtiles << 2), (prevCount - sprtiles) << 2 );
		VDP_FillVRAM_16K( 0, sprtiles << 3, (prevCount - sprtiles) << 3 );
	}
	//     ======================= AT THIS POINT: DRAWING TO DISPLAY HAS COMPLETED
	prevCount = sprtiles;
	// flip red/green for second half of cycle
	if (sprtiles > 0)
	{
		u8* a = spratr + (sproff[f] << 2) + 3;
		for (i16 i = 0; i < sprtiles; i++, a += 4) if (*a == 8) *a = 2; else if (*a == 2) *a = 8;
	}
	base += 128;
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