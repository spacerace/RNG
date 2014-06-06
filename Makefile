CC = gcc
WARN = -Wall -Werror
OPT = -O2
LINK = -lm -lpng
TARGET = rand_test

all:
	$(CC) $(WARN) $(OPT) -c main.c -o main.o
	$(CC) $(WARN) $(OPT) -c kiss.c -o kiss.o
	$(CC) $(WARN) $(OPT) -c xorshift.c -o xorshift.o
	$(CC) $(WARN) $(OPT) -c libcrnd.c -o libcrnd.o
	$(CC) $(WARN) $(OPT) -c png.c -o png.o
	$(CC) $(OPT) $(LINK) *.o -o $(TARGET)
	size *.o $(TARGET)

clean:
	rm *.o
	rm $(TARGET)
