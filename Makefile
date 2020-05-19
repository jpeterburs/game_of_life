program: main.o
	gcc -o game_of_life main.o game_of_life.o

main.o: main.c
	gcc -c main.c

game_of_life.o: game_of_life.c
	gcc -c game_of_life.c
