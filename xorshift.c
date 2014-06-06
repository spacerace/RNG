/* for more information see:
 * 	de.wikipedia.org/wiki/Xorshift
 *
 * (c) 2014 Nils Stec and Others (see link above)
 *
 */

#include "rnd.h"

uint32_t xorshift32() {
	static uint32_t x = 1;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}


