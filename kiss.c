#include "rnd.h"

static uint32_t x = 123456789;
static uint32_t y = 26;
static uint32_t z = 551241;
static uint32_t c = 12312313;

uint32_t kiss() {
	uint64_t t;

	x = 69069 * x + 12345;

	y ^= y << 13;
	y ^= y >> 17;
	y ^= y << 5;

	t = 698769069ULL * z + c;
	c = t >> 32;
	z = (uint32_t) t;

	return x + y + z;
}

