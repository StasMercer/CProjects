# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wconversion -g
LDLIBS=-lm -lcurses
OUTPUT=bmp

# targets
all: $(OUTPUT)

$(OUTPUT): main.o bmp.o transformations.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS)  main.o bmp.o transformations.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

transformations.o: transformations.c transformations.h
	$(CC) $(CFLAGS) -c transformations.c $(LDLIBS) -o transformations.o

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c $(LDLIBS) -o bmp.o


# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o