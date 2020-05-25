#include <stdio.h>
#include <stdlib.h>
#include "console_helper.h"
#include "game_of_life.h"

struct options start_menu()
{
    struct options current_options;

    allow_special_chars();
    build_frame(80, 15);

    set_cursor(25, 2);
    printf("Welcome to the game of life");

    set_cursor(10, 5);
    printf("Please input your game settings.");

    set_cursor(5, 6);
    printf("Height: ");
    scanf("%i", &current_options.height);
    fflush(stdin);

    set_cursor(5, 7);
    printf("Width: ");
    scanf("%i", &current_options.width);
    fflush(stdin);

    set_cursor(5, 8);
    printf("Iterations per second: ");
    scanf("%i", &current_options.iterations_per_second);
    fflush(stdin);


    set_cursor(10, 10);
    printf("\tPlease select your characters.");

    set_cursor(5, 11);
    printf("Alive cells: ");
    scanf("%c", &current_options.alive);
    fflush(stdin);

    set_cursor(5, 12);
    printf("Dead cells: ");
    scanf("%c", &current_options.dead);
    fflush(stdin);

    return current_options;
}
