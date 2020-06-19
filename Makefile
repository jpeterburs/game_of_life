#  -g    		adds debugging information to the executable file
#  -Werror 	turns all compiler warnings into errors, and thus filing the compiling process
CC = gcc
CFLAGS  = -g -Werror
TARGET = bin/game_of_life

all: game_of_life

game_of_life: main.o game_of_life.o console_helper.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o game_of_life.o console_helper.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game_of_life.o: game_of_life.c game_of_life.h
	$(CC) $(CFLAGS) -c game_of_life.c

console_helper.o: console_helper.c console_helper.h
	$(CC) $(CFLAGS) -c console_helper.c

clean:
	$(RM) game_of_life *.o *~
