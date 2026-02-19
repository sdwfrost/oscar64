#include "gametank.h"

// Interrupt vectors at $FFFA-$FFFF
#pragma data(boot)

__export struct GTVectors
{
	void * nmi, * reset, * irq;
} gtvectors = {
	nullptr,          // NMI - unused for now
	(void *)0xff80,   // RESET - points to startup code
	nullptr           // IRQ - unused for now
};

#pragma data(data)
