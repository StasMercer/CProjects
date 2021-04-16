# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
LDLIBS=-lm
OUTPUT=ps1

# targets
all: $(OUTPUT)

$(OUTPUT): playfair.o bmp.o main.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) playfair.o bmp.o main.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

playfair.o: playfair.c playfair.h
	$(CC) $(CFLAGS) -c playfair.c $(LDLIBS) -o playfair.o

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c $(LDLIBS) -o bmp.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o