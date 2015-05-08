CC = gcc
CFLAGS = -Wall -g -I.

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

all: traverse showfat showsector help fshell
	
traverse: traverse.o
	$(CC) -o traverse traverse.o $(CFLAGS)
	
showfat: showfat.o
	$(CC) -o showfat showfat.o $(CFLAGS)
	
showsector: showsector.o
	$(CC) -o showsector showsector.o $(CFLAGS)
	
help: help.o
	$(CC) -o help help.o $(CFLAGS)

fshell: fshell.o
	$(CC) -o fshell fshell.o $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o fshell
	rm -f *.o traverse
	rm -f *.o showfat
	rm -f *.o showsector
	rm -f *.o help
