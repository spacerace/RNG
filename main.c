#include "rnd.h"

#define IMG_X	450
#define IMG_Y	450
#define ROUNDS	7500

int main(int argc, char **argv) {

	uint16_t x, y;
	uint32_t loops;
	uint8_t buffer[7];
	FILE *fptr;
	clock_t begin, end;
	clock_t len_kiss;
	clock_t len_xorshift;
	clock_t len_urandom;
	clock_t len_libc;
	double t;

	int color = 1;

#define COLORDEF_RED 255
#define COLORDEF_GREEN 255
#define COLORDEF_BLUE 255

	bitmap_t img_kiss;
	bitmap_t img_xorshift;
	bitmap_t img_urandom;
	bitmap_t img_libc;

	img_kiss.width = IMG_X;
	img_kiss.height = IMG_Y;
	img_xorshift.width = IMG_X;
	img_xorshift.height = IMG_Y;
	img_urandom.width = IMG_X;
	img_urandom.height = IMG_Y;
	img_libc.width = IMG_X;
	img_libc.height = IMG_Y;

	img_kiss.pixels = calloc(sizeof(pixel_t), img_kiss.width*img_kiss.height);
	img_xorshift.pixels = calloc(sizeof(pixel_t), img_xorshift.width*img_xorshift.height);
	img_urandom.pixels = calloc(sizeof(pixel_t), img_urandom.width*img_urandom.height);
	img_libc.pixels = calloc(sizeof(pixel_t), img_libc.width*img_libc.height);
	
	printf("plotting %d pixels on each image\n", ROUNDS);
	printf("CLOCKS_PER_SEC=%d\n", (unsigned int)CLOCKS_PER_SEC);
	printf("libc ... ");
	begin = clock();
	for(loops = 0; loops < ROUNDS; loops++) {
		x = (uint16_t)(libc_rand()%IMG_X);
		y = (uint16_t)(libc_rand()%IMG_Y);

		pixel_t *pixel = pixel_at(&img_libc, x, y);
		if(color) {
			pixel->red = libc_rand()&0xff;
			pixel->green = libc_rand()&0xff;
			pixel->blue = libc_rand()&0xff;
		} else {
			pixel->red = COLORDEF_RED;
			pixel->green = COLORDEF_GREEN;
			pixel->blue = COLORDEF_BLUE;
			/* we want same random number sequence as in colored mode, 
			 * so ask RNG for the other random numbers, but put them
			 * into bitbucket */
			libc_rand();
			libc_rand();
			libc_rand();
		}
	}
	end = clock();
	len_libc = end - begin;
	t = len_libc / CLOCKS_PER_SEC;
	printf("done in %fS (%d clocks)\n", t, (unsigned int)len_libc);
	if(color) save_png(&img_libc, "vis-rnd-libc.png");
	else save_png(&img_libc, "vis-rnd-libc-mono.png");

	printf("xorshift ... ");
	begin = clock();
	for(loops = 0; loops < ROUNDS; loops++) {
		x = (uint16_t)(xorshift32()%IMG_X);
		y = (uint16_t)(xorshift32()%IMG_Y);

		pixel_t *pixel = pixel_at(&img_xorshift, x, y);
		if(color) {
			pixel->red = xorshift32()&0xff;
			pixel->green = xorshift32()&0xff;
			pixel->blue = xorshift32()&0xff;
		} else {
			pixel->red = COLORDEF_RED;
			pixel->green = COLORDEF_GREEN;
			pixel->blue = COLORDEF_BLUE;
			xorshift32();
			xorshift32();
			xorshift32();
		}
	}
	end = clock();
	len_xorshift = end - begin;
	t = len_xorshift / CLOCKS_PER_SEC;
	printf("done in %fS (%d clocks)\n", t, (unsigned int)len_xorshift);
	if(color) save_png(&img_xorshift, "vis-rnd-xorshift.png");
	else save_png(&img_xorshift, "vis-rnd-xorshift-mono.png");

	printf("kiss ... ");
	begin = clock();
	for(loops = 0; loops < ROUNDS; loops++) {
		x = (uint16_t)(kiss()%IMG_X);
		y = (uint16_t)(kiss()%IMG_Y);

		pixel_t * pixel = pixel_at(&img_kiss, x, y);
		if(color) {
			pixel->red = kiss()&0xff;
			pixel->green = kiss()&0xff;
			pixel->blue = kiss()&0xff;
		} else {
			pixel->red = COLORDEF_RED;
			pixel->green = COLORDEF_GREEN;
			pixel->blue = COLORDEF_BLUE;
			kiss();
			kiss();
			kiss();
		}

	}
	end = clock();
	len_kiss = end - begin;
	t = len_xorshift / CLOCKS_PER_SEC;
	printf("done in %fS (%d clocks)\n", t, (unsigned int)len_kiss);
	if(color) save_png(&img_kiss, "vis-rnd-kiss.png");
	else save_png(&img_kiss, "vis-rnd-kiss-mono.png");


	printf("/dev/urandom ... ");
	fptr = fopen("/dev/urandom", "r");
	begin = clock();
	for(loops = 0; loops < ROUNDS; loops++) {
		pixel_t *pixel = pixel_at(&img_urandom, x, y);
		fread(&buffer, 1, 7, fptr);

		x = (uint16_t)(((buffer[0]<<8)|buffer[1])%IMG_X);
		y = (uint16_t)(((buffer[2]<<8)|buffer[3])%IMG_Y);
		if(color) {
			pixel->red = buffer[4];
			pixel->green = buffer[5];
			pixel->blue = buffer[6];
		} else {
			pixel->red = COLORDEF_RED;
			pixel->green = COLORDEF_GREEN;
			pixel->blue = COLORDEF_BLUE;

		}
	}
	end = clock();
	len_urandom = end - begin;
	t = (double)((unsigned int)len_urandom / CLOCKS_PER_SEC * 1000.0);
	printf("done in %fS (%d clocks)\n", t, (unsigned int)len_urandom);
	fclose(fptr);
	if(color) save_png(&img_urandom, "vis-rnd-urandom.png");
	else save_png(&img_urandom, "vis-rnd-urandom-mono.png");

	return 0;

}
