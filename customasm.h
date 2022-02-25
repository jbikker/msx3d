void VDP_WriteVRAM_16K_4( const u8* src, u16 dest )
{
	__asm
		ld		a, e
		di
		out( 0x99 ), a
		ld		a, d
		ei
		out( 0x99 ), a
		ld		c, #0x98
		outi
		outi
		outi
		outi
	__endasm;
}

void VDP_WriteVRAM_16K_8( const u8* src, u16 dest )
{
	__asm
		ld		a, e
		di
		out( 0x99 ), a
		ld		a, d
		ei
		out( 0x99 ), a
		ld		c, #0x98
		outi
		outi
		outi
		outi
		outi
		outi
		outi
		outi
	__endasm;
}

void VDP_WriteVRAM_16K_12( const u8* src, u16 dest )
{
	src, dest;
	__asm
		ld		a, e
		di
		out( 0x99 ), a
		ld		a, d
		ei
		out( 0x99 ), a
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
	__endasm;
}

void VDP_WriteVRAM_16K_12x12( const u8* src )
{
	__asm
		ld		a, #0xCA
		di
		out( 0x99 ), a
		ld		a, #0x54
		ei
		out( 0x99 ), a
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
	__endasm;
}