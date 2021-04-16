# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wconversion -g
LDLIBS=-lm -lcurses
OUTPUT=game

# targets
all: $(OUTPUT)

$(OUTPUT): main.o game.o container.o backpack.o command.o item.o parser.o room.o world.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS)  main.o game.o container.o backpack.o command.o item.o parser.o room.o world.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

container.o: container.c container.h
	$(CC) $(CFLAGS) -c container.c $(LDLIBS) -o container.o

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c $(LDLIBS) -o game.o

backpack.o: backpack.c backpack.h
	$(CC) $(CFLAGS) -c backpack.c $(LDLIBS) -o backpack.o

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c $(LDLIBS) -o command.o

item.o: item.c item.h
	$(CC) $(CFLAGS) -c item.c $(LDLIBS) -o item.o

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c $(LDLIBS) -o parser.o

room.o: room.c room.h
	$(CC) $(CFLAGS) -c room.c $(LDLIBS) -o room.o

world.o: world.c world.h
	$(CC) $(CFLAGS) -c world.c $(LDLIBS) -o world.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o