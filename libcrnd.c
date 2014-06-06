/* according to "man 3 rand" POSIX.1-2001 gives the following example
 * of an implementation of rand() and srand().
 */


#include "rnd.h"

static unsigned long next = 1;

/* RAND_MAX assumed to be 32767 */

int libc_rand(void) {
	next = next * 1103515245 + 12345;
	return((unsigned)(next/65536) % 32768);
}

void libc_srand(unsigned int seed) {
	next = seed;
}



