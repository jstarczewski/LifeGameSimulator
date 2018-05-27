CC=gcc
CFLAGS= -std=c99 -c -Wall -pedantic

all: life_game_generator

life_game_generator: main.o board.o game_board.o states.o png_gen.o log.o
	$(CC) -o life_game_generator main.o game_board.o board.o states.o png_gen.o log.o -lpng

main.o: main.c
	$(CC) $(CFLAGS) main.c

game_board.o: game_board.c game_board.h
	$(CC) $(CFLAGS) game_board.c

board.o: board.c board.h
	$(CC) $(CFLAGS) board.c

states.o: states.c states.h
	$(CC) $(CFLAGS) states.c

png_gen.o: png_gen.c png_gen.h
	$(CC) $(CFLAGS) -lpng png_gen.c

log.o: log.c log.h
	$(CC) $(CFLAGS) log.c

clean: 
	rm *o life_game_generator
