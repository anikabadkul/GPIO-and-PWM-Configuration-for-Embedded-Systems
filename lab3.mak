CC=gcc
CFLAGS=-Wall

all: lab3.exe

lab3.exe: lab3.c
	$(CC) $(CFLAGS) -o lab3.exe lab3.c 

.PHONY: clean
clean:
	del lab3.exe