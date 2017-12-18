#ifndef BLOCK
#define BLOCK

#include "gen.h"
#include <stdiny.h>

struct block{
	uint64_t pos;
	volatile uint8_t arr[512][4096];
};

#endif
