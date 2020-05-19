#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CC = gcc
CFLAGS  = -g -Wall

all: game_of_life

game_of_life: game_of_life.o
	$(CC) $(CFLAGS) -o game_of_life game_of_live.o

main.o: main.c
	$(CC) $(CFLAGS) -o main.c

game_of_life.o: game_of_live.c game_of_live.h
	$(CC) $(CFLAGS) -c game_of_life.c

clean:
	$(RM) game_of_life *.o *~
