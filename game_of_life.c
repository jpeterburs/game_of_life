#include <stdio.h>
#include <stdlib.h>
#include "game_of_life.h"

struct options start_menu()
{
    struct options current_options;

    printf("\t\tWelcome to the game of life\n\n");

    printf("\tPlease input your game settings.\n");
    printf("Height: ");
    scanf("%i", &current_options.height);
    fflush(stdin);

    printf("Width: ");
    scanf("%i", &current_options.width);
    fflush(stdin);

    printf("Iterations per second: ");
    scanf("%i", &current_options.iterations_per_second);
    fflush(stdin);

    printf("\n");

    printf("\tPlease select your characters.\n");
    printf("Alive cells: ");
    scanf("%c", &current_options.alive);
    fflush(stdin);

    printf("Dead cells: ");
    scanf("%c", &current_options.dead);
    fflush(stdin);

    return current_options;
}
