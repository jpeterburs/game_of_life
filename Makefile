program: main.o
	gcc -o game_of_life main.o

main.o: main.c
	gcc -c main.c
