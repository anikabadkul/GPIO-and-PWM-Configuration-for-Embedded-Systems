CC=gcc
CFLAGS=-Wall

all: testGPIO.exe

testGPIO.exe: testGPIO.c
	$(CC) $(CFLAGS) -o testGPIO.exe testGPIO.c 

.PHONY: clean
clean:
	del testGPIO.exe