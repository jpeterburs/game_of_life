/**
 *  Conway's Game of Life
 *  https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 *  This is a zero-player game, meaning that its a evolution simulator.
 *
 *  Authors: Eduard Rempel, Jonas Peterburs, Milan Wiehe
 *  Created at: 2020/05/19
 **/
#include <stdio.h>
#include <stdlib.h>
#include "console_helper.h"
#include "game_of_life.h"

/**
 *  Creates a simple framed start menu for the player to setup his options.
 **/
struct options start_menu()
{
    struct options current_options;

    allow_special_chars(); // Enable the usage for special characters.
    build_frame(80, 15); // Create an empty frame for the start menu

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

/**
 *  Creates an empty play field initialized with random cells
 **/
void create_field(struct options current_options, int field[][current_options.width])
{
    int i, j, state;

    for(i = 0; i < current_options.height; i++)
    {
        for(j = 0; j < current_options.width; j++)
        {
            state = rand();
            printf("%i", state);
            if (state%2 == 0)
            {
                field[i][j] = 1;
            }
            else
            {
                field[i][j] = 0;
            }
        }
    }
}

/**
 *  Copy field from source_field to target_field
 **/
void copy_field(struct options current_options, int source_field[][current_options.width], int target_field[][current_options.width])
{
    int i, j;
    for(i = 0; i < current_options.height; i++)
    {
        for(j = 0; j < current_options.width; j++)
        {
            target_field[i][j] = source_field[i][j]; //Initial value for cells
        }
    }
}

/**
 *  Outputs a field of cells to console
 **/
void print_field(struct options current_options, int field[][current_options.width])
{
    clear_screen();

    int i, j;
    for(i = 0; i < current_options.height; i++)
    {

        for(j = 0; j < current_options.width; j++)
        {
            //Checks if cell is dead
            if(field[i][j] == 0)
            {
                printf("%c ", current_options.dead);
            }
            else
            {
                printf("%c ", current_options.alive);
            }
        }
        printf("\n");
    }
    printf("\n");
}

/**
 *  Generate rule set from user input
 **/
struct rule_set input_rule_set()
{
    struct rule_set game_rules;

    clear_screen();
    build_frame(80, 15); // Create an empty frame for the start menu

    set_cursor(5, 6);
    printf("Maximum number of neighbors to revive: ");
    scanf("%i", &game_rules.max_revive);
    fflush(stdin);

    set_cursor(5, 7);
    printf("Minimum number of neighbors to revive: ");
    scanf("%i", &game_rules.min_revive);
    fflush(stdin);

    set_cursor(5, 8);
    printf("Maximum number of neighbors to survive: ");
    scanf("%i", &game_rules.max_survive);
    fflush(stdin);

    set_cursor(5, 9);
    printf("Minimum number of neighbors to survive: ");
    scanf("%i", &game_rules.min_survive);
    fflush(stdin);

    return game_rules;
};

void calculate_next_step(struct options current_options, int field[][current_options.width], struct rule_set game_rules, int next_field[][current_options.width])
{
    int i, j;
    int i_offset, j_offset;
    int count_alive = 0;

    for(i = 0; i < current_options.height; i++)
    {
        for(j = 0; j < current_options.width; j++)
        {
            for(i_offset = -1; i_offset < 2; i_offset++)
            {
                for(j_offset = -1; j_offset < 2; j_offset++)
                {
                    int pos_i = i + i_offset;
                    int pos_j = j + j_offset;

                    if(pos_i >= 0 && pos_i < current_options.height && pos_j >= 0 && pos_j < current_options.width && !(pos_i == i && pos_j == j))
                    {
                        count_alive += field[pos_i][pos_j];
                    }
                }
            }

            if(field[i][j] == 1)
            {
                if(count_alive > game_rules.max_survive || count_alive < game_rules.min_survive)
                {
                    next_field[i][j] = 0;
                }
                else
                {
                    next_field[i][j] = 1;
                }
            }
            else
            {
                if(count_alive > game_rules.max_revive || count_alive < game_rules.min_revive)
                {
                    next_field[i][j] = 0;
                }
                else
                {
                    next_field[i][j] = 1;
                }
            }

            count_alive = 0;
        }
    }
}
