#ifndef GAMETANK_GAMETANK_H
#define GAMETANK_GAMETANK_H

#include <c64/types.h>

// System Control Registers
struct GTSystem
{
	volatile byte audio_reset;    // $2000 - Audio coprocessor reset
	volatile byte audio_nmi;      // $2001 - Audio coprocessor NMI
	byte          _pad0[3];       // $2002-$2004
	volatile byte banking;        // $2005 - Banking & video control
	volatile byte audio_rate;     // $2006 - Audio sample rate config
	volatile byte dma_flags;      // $2007 - DMA/Video control flags
	volatile byte gamepad1;       // $2008 - Player 1 input
	volatile byte gamepad2;       // $2009 - Player 2 input
};

#define gtsys (*((struct GTSystem *)0x2000))

// Banking register bits ($2005)
#define BANK_GRAM_PAGE(n) ((n) & 0x07)
#define BANK_VRAM_SELECT  0x08
#define BANK_CLIP_X       0x10
#define BANK_CLIP_Y       0x20
#define BANK_RAM(n)       (((n) & 0x03) << 6)

// DMA flags ($2007)
#define DMA_ENABLE         0x01
#define DMA_PAGE_OUT       0x02
#define DMA_NMI            0x04
#define DMA_COLORFILL      0x08
#define DMA_GCARRY         0x10
#define DMA_CPU_TO_VRAM    0x20
#define DMA_IRQ            0x40
#define DMA_OPAQUE         0x80

// Blitter Registers
struct GTBlitter
{
	volatile byte vx;       // $4000 - Dest X in framebuffer
	volatile byte vy;       // $4001 - Dest Y in framebuffer
	volatile byte gx;       // $4002 - Source X in sprite RAM
	volatile byte gy;       // $4003 - Source Y in sprite RAM
	volatile byte width;    // $4004 - Width (bit 7 = H flip)
	volatile byte height;   // $4005 - Height (bit 7 = V flip)
	volatile byte start;    // $4006 - Write to trigger DMA
	volatile byte color;    // $4007 - Fill color
};

#define gtblitter (*((struct GTBlitter *)0x4000))

// VIA 6522 Registers
struct GTVIA
{
	volatile byte iorb;     // $2800 - I/O Register B
	volatile byte iora;     // $2801 - I/O Register A (SPI for ROM banking)
	volatile byte ddrb;     // $2802 - Data Direction B
	volatile byte ddra;     // $2803 - Data Direction A
	volatile byte t1cl;     // $2804 - Timer 1 Counter Low
	volatile byte t1ch;     // $2805 - Timer 1 Counter High
	volatile byte t1ll;     // $2806 - Timer 1 Latch Low
	volatile byte t1lh;     // $2807 - Timer 1 Latch High
	volatile byte t2cl;     // $2808 - Timer 2 Counter Low
	volatile byte t2ch;     // $2809 - Timer 2 Counter High
	volatile byte sr;       // $280A - Shift Register
	volatile byte acr;      // $280B - Auxiliary Control
	volatile byte pcr;      // $280C - Peripheral Control
	volatile byte ifr;      // $280D - Interrupt Flag
	volatile byte ier;      // $280E - Interrupt Enable
	volatile byte iora_nh;  // $280F - I/O Register A (no handshake)
};

#define gtvia (*((struct GTVIA *)0x2800))

// VIA Port A SPI bits (for ROM bank select)
#define VIA_SPI_CLK   0x01
#define VIA_SPI_MOSI  0x02
#define VIA_SPI_CS    0x04

// Gamepad button masks (from two consecutive reads)
#define INPUT_UP      0x0808
#define INPUT_DOWN    0x0404
#define INPUT_LEFT    0x0200
#define INPUT_RIGHT   0x0100
#define INPUT_A       0x0010
#define INPUT_B       0x1000
#define INPUT_C       0x2000
#define INPUT_START   0x0020

// Audio coprocessor RAM
#define GT_AUDIO_RAM  ((volatile byte *)0x3000)

#pragma compile("gametank.c")

#endif
