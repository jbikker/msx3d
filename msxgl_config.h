// __________________________
// ██▀█▀██▀▀▀█▀▀█▀█  ▄▄▄ ▄▄  │   ▄▄▄                ▄▄      
// █  ▄ █▄ ▀██▄ ▀▄█ ██   ██  │  ▀█▄  ▄▀██ ▄█▄█ ██▀▄ ██  ▄███
// █  █ █▀▀ ▄█  █ █ ▀█▄█ ██▄▄│  ▄▄█▀ ▀▄██ ██ █ ██▀  ▀█▄ ▀█▄▄
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀──────────┘                 ▀▀
//  Library configuration
//─────────────────────────────────────────────────────────────────────────────
#pragma once

//-----------------------------------------------------------------------------
// BUILD
//-----------------------------------------------------------------------------

// Target
// - TARGET_BIN ...................	BASIC binary program
// - TARGET_ROM16 ................. 16KB ROM in page 1
// - TARGET_ROM16P2 ............... 16KB ROM in page 2
// - TARGET_ROM32 ................. 32KB ROM in page 1-2
// - TARGET_ROM32P0 ............... 32KB ROM in page 0-1
// - TARGET_ROM48 ................. 48KB ROM in page 0-2
// - TARGET_DOS ................... MSX-DOS program
// - TARGET_DOSARG ................ MSX-DOS program (using command line arguments)
// TARGET is defined by the build tool

// Target type
// - TARGET_TYPE_BIN .............. BASIC binary program
// - TARGET_TYPE_ROM .............. ROM
// - TARGET_TYPE_DOS .............. MSX-DOS program
// TARGET_TYPE is defined by the build tool

// MSX version
// - MSX_1 ........................ MSX
// - MSX_2 ........................ MSX 2
// - MSX_2P ....................... MSX 2+
// - MSX_TR ....................... MSX turbo R
// MSX_VERSION is defined by the build tool

//-----------------------------------------------------------------------------
// BIOS MODULE
//-----------------------------------------------------------------------------

// Default slot BIOS access
// - BIOS_CALL_DIRECT ............. Use direct access to Bios routines (ROM slot must be selected in corresponding page)
// - BIOS_CALL_INTERSLOT .......... Use inter-slot access to Bios routines (through CALSLT routine)
#define BIOS_CALL_MAINROM			BIOS_CALL_DIRECT
#define BIOS_CALL_SUBROM			BIOS_CALL_INTERSLOT
#define BIOS_CALL_DISKROM			BIOS_CALL_INTERSLOT

// MAIN-Bios module setting
#define BIOS_USE_MAINROM			1	// Allow use of Main-ROM routines
#define BIOS_USE_VDP				1	// Give access to Main-ROM routines related to VDP
#define BIOS_USE_PSG				1	// Give access to Main-ROM routines related to PSG
#define BIOS_USE_SUBROM				1	// Allow use of Sub-ROM routines (MSX 2/2+/turbo R)
#define BIOS_USE_DISKROM			1	// Allow use of Disk-ROM routines

//-----------------------------------------------------------------------------
// VDP MODULE
//-----------------------------------------------------------------------------

// VRAM addressing unit
// - VDP_VRAM_ADDR_14 ............. Use 14-bits 16K VRAM addressing for MSX 1 (u16)
// - VDP_VRAM_ADDR_17 ............. Use 17-bits 128K VRAM addressing for MSX 2/2+/turbo R (u32)
#define VDP_VRAM_ADDR				VDP_VRAM_ADDR_14

// VDP X/Y units
// - VDP_UNIT_U8 .................. X and Y use 8-bits values
// - VDP_UNIT_X16 ................. X use 16-bits and Y use 8-bits values
// - VDP_UNIT_Y16 ................. X use 8-bits and Y use 16-bits values
// - VDP_UNIT_U16 ................. X and Y use 16-bits values
#define VDP_UNIT					VDP_UNIT_U8

// VDP screen modes (additionnal limitations come from the selected MSX_VERSION)
#define VDP_USE_MODE_T1				1	// MSX1		Screen 0 Width 40
#define VDP_USE_MODE_MC				1	// MSX1		Screen 3
#define VDP_USE_MODE_G1				1	// MSX1		Screen 1
#define VDP_USE_MODE_G2				1	// MSX1		Screen 2
#define VDP_USE_MODE_T2				0	// MSX2		Screen 0 Width 80
#define VDP_USE_MODE_G3				0	// MSX2		Screen 4
#define VDP_USE_MODE_G4				0	// MSX2		Screen 5
#define VDP_USE_MODE_G5				0	// MSX2		Screen 6
#define VDP_USE_MODE_G6				0	// MSX2		Screen 7
#define VDP_USE_MODE_G7				0	// MSX2/2+	Screen 8, 10, 11 & 12

//-----------------------------------------------------------------------------
// INPUT MODULE
//-----------------------------------------------------------------------------

// Input module setting
#define INPUT_USE_JOYSTICK			0
#define INPUT_USE_KEYBOARD			1
#define INPUT_USE_MANAGER			0

//-----------------------------------------------------------------------------
// DRAW MODULE
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRINT MODULE
//-----------------------------------------------------------------------------

// Print module setting
#define PRINT_USE_TEXT				1	// Allow use of Text font (T1-T2, G1-G3)
#define PRINT_USE_BITMAP			0	// Allow use of Bitmap font (G4-G7)
#define PRINT_USE_VRAM				0	// Allow use of VRAM stored font (G4-G7)
#define PRINT_USE_SPRITE			0	// Allow use of Sprite font (G3-G7)
#define PRINT_USE_FX_SHADOW			0	// [Bitmap] Allow use of text shadow
#define PRINT_USE_FX_OUTLINE		0	// [Bitmap] Allow use of text outline
#define PRINT_USE_GRAPH				0	// Allow use of character lines and boxes
#define PRINT_USE_VALIDATOR			0	// Add validator character code
#define PRINT_USE_UNIT				1	// Display integer type (h: hexadecimal, b: binary)
#define PRINT_USE_FORMAT			0
#define PRINT_USE_32B				0
#define PRINT_SKIP_SPACE			1	// Skill space character
#define PRINT_COLOR_NUM				12	// 1 color per line
// - PRINT_WIDTH_1
// - PRINT_WIDTH_6
// - PRINT_WIDTH_8
// - PRINT_WIDTH_X
#define PRINT_WIDTH					PRINT_WIDTH_X
// - PRINT_HEIGHT_1
// - PRINT_HEIGHT_8
// - PRINT_HEIGHT_X
#define PRINT_HEIGHT				PRINT_HEIGHT_1

//-----------------------------------------------------------------------------
// GAME MODULE
//-----------------------------------------------------------------------------

// Game state setting
#define GAME_USE_STATE				0
#define GAME_USE_STATE_TRANSITION		0
#define GAME_USE_VSYNC				0
#define GAME_USE_LOOP				0

//-----------------------------------------------------------------------------
// AUDIO 
//-----------------------------------------------------------------------------

// PSG options
#define PSG_CHIP				PSG_INTERNAL
#define PSG_ACCESS				PSG_INDIRECT
#define PSG_USE_NOTES				1
#define PSG_USE_RESUME				1

// MSX-Music options
#define MSXAUDIO_USE_RESUME			1

// MSX-Audio options
#define MSXMUSIC_USE_RESUME			1

// SCC options
#define SCC_USE_EXTA				0
#define SCC_USE_RESUME				0
// - SCC_SLOT_DIRECT .............. Program on a SCC cartridge
// - SCC_SLOT_FIXED	............... Fixed slot-id (non-expanded second cartridge slot)
// - SCC_SLOT_USER ................ Defined by the user
// - SCC_SLOT_AUTO ................ First auto-detected cartridge
#define SCC_SLOT_MODE				SCC_SLOT_AUTO

// VGM supported chip
#define VGM_USE_PSG				0
#define VGM_USE_MSXMUSIC			0
#define VGM_USE_MSXAUDIO			0
#define VGM_USE_SCC				0

// PCM-Encoder supported frequency (more than 1 value allowed)
#define PCMENC_FREQ					PCMENC_8K | PCMENC_11K | PCMENC_22K | PCMENC_44K

//-----------------------------------------------------------------------------
// MSXi MODULE
//-----------------------------------------------------------------------------

// MSXi compressor support
#define MSXi_USE_COMP_NONE			1
#define MSXi_USE_COMP_CROP16			0
#define MSXi_USE_COMP_CROP32			0
#define MSXi_USE_COMP_CROP256			0
#define MSXi_USE_COMP_CROPLINE16		0
#define MSXi_USE_COMP_CROPLINE32		0
#define MSXi_USE_COMP_CROPLINE256		0
#define MSXi_USE_COMP_RLE0			0
#define MSXi_USE_COMP_RLE4			0
#define MSXi_USE_COMP_RLE8			0

//-----------------------------------------------------------------------------
// MATH MODULE
//-----------------------------------------------------------------------------

// Random methods
// - RANDOM_8_NONE ................ No 8-bits random
// - RANDOM_8_REGISTER ............ R Register value (7-bits)
// - RANDOM_8_RACC ................ R Register accumulation (7-bits)
// - RANDOM_8_ION ................. Ion Random
// - RANDOM_8_MEMORY .............. Memory Peek from R
#define RANDOM_8_METHOD				RANDOM_8_ION
// - RANDOM_16_NONE ............... No 16-bits random
// - RANDOM_16_LINEAR ............. Linear congruential
// - RANDOM_16_XORSHIFT ........... XOR Shift
// - RANDOM_16_LFSR_LCG ........... Combined LFSR/LCG
#define RANDOM_16_METHOD			RANDOM_16_XORSHIFT

//-----------------------------------------------------------------------------
// COMPRESS 
//-----------------------------------------------------------------------------

// RLEp compression
#define COMPRESS_USE_RLEP			0
#define COMPRESS_USE_RLEP_DEFAULT		1
#define COMPRESS_USE_RLEP_FIXSIZE		1

//-----------------------------------------------------------------------------
// MISC
//-----------------------------------------------------------------------------

// Profiler method
// - PROFILE_DISABLE .............. No profiler
// - PROFILE_OPENMSX_G ............ Grauw profile script for OpenMSX
// - PROFILE_OPENMSX_S ............ Salutte profile script for OpenMSX
#define PROFILE_MODE				PROFILE_OPENMSX_G
#define PROFILE_LEVEL				10 
