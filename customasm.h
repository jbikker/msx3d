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