#ifndef __RND_H__
#define __RND_H__

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include <math.h>
#include <malloc.h>
#include <png.h>

#include <time.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_t;

typedef struct {
	pixel_t *pixels;
	size_t width;
	size_t height;
} bitmap_t;

pixel_t *pixel_at(bitmap_t *bitmap, int x, int y);
int save_png(bitmap_t *bitmap, const char *path);

uint32_t xorshift32();
uint32_t kiss();

int libc_rand(void);
void libc_srand(unsigned int seed);

#endif


