CC=gcc
CFLAGS=-Wall

all: testPWM.exe

testPWM.exe: testPWM.c
	$(CC) $(CFLAGS) -o testPWM.exe testPWM.c 

.PHONY: clean
clean:
	del testPWM.exe