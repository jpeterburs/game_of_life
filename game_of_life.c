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
#include <time.h>
#include <string.h>
#include <windows.h>
#include "console_helper.h"
#include "game_of_life.h"

/**
 *  This start the game of life; May the games begin!
 **/
void start_game()
{
    struct options current_options;

    do
    {
        // Display start menu, until options are valid
        current_options = start_menu();

        if (validate_input(current_options) == 1)
        {
            printf("Options invalid.");
            Sleep(1500);
        }
    } while (validate_input(current_options) == 1);


    // Initialize fields
    int field[current_options.height][current_options.width];
    int next_field[current_options.height][current_options.width];

    int pre_last_state[current_options.height][current_options.width];
    int last_state[current_options.height][current_options.width];
    int iteration = 0;
    int sleep_time = 1000/current_options.iterations_per_second;

    // Create initial field
    create_field(current_options, field);

    // Run the game, until a won state is detected
    while(has_won(current_options, field, pre_last_state) != 1)
    {
        // Print current field
        print_field(current_options, field, iteration);

        // Calculation of the next iteration
        calculate_next_step(current_options, field, next_field);

        // cache last fields for state determination
        copy_field(current_options, last_state, pre_last_state);
        copy_field(current_options, field, last_state);

        copy_field(current_options, next_field, field);

        iteration++;

        if (current_options.mode == 'm' || current_options.mode == 'M')
        {
            char next;
            printf("\n");
            printf("Press [Enter] for next iteration, [a] or [A] for automatic mode and [s] or [S] to save current iteration.");
            scanf("%c", &next);
            fflush(stdin);

            if (next == 'a' || next == 'A')
            {
                current_options.mode = next;
            }
            else if (next == 's' || next == 'S')
            {
                save_field(current_options, last_state);
            }
        }
        else
        {
            Sleep(sleep_time);
        }
    }

    printf("You have won! Maybe ...\n");
    Sleep(2500);
}

/**
 *  Creates a simple framed start menu for the player to setup his options.
 **/
struct options start_menu()
{
    struct options current_options;

    allow_special_chars(); // Enable the usage for special characters.
    build_frame(80, 20); // Create an empty frame for the start menu

    int row = 2;
    char load_file;

    set_cursor(25, row++);
    printf("Welcome to the game of life");

    row++;

    set_cursor(10, row++);
    printf("Please input your game settings.");

    set_cursor(5, row++);
    printf("Height (min 3): ");
    scanf("%i", &current_options.height);
    fflush(stdin);

    set_cursor(5, row++);
    printf("Width (min 3): ");
    scanf("%i", &current_options.width);
    fflush(stdin);

    set_cursor(5, row++);
    printf("Iterations per second (1 - 10): ");
    scanf("%i", &current_options.iterations_per_second);
    fflush(stdin);

    set_cursor(5, row++);
    printf("Manual ([m]/[M]) or Automatic ([a]/[A]) mode: ");
    scanf("%c", &current_options.mode);
    fflush(stdin);

    set_cursor(5, row++);
    printf("Use custom rules? (yes [y]/[Y] or no [n]/[N]): ");
    scanf("%c", &load_file);
    fflush(stdin);

    row++;

    set_cursor(10, row++);
    printf("\tPlease select your characters. (Cannot be the same)");

    set_cursor(5, row++);
    printf("Alive cells: ");
    scanf("%c", &current_options.alive);
    fflush(stdin);

    set_cursor(5, row++);
    printf("Dead cells: ");
    scanf("%c", &current_options.dead);
    fflush(stdin);

    row++;

    if (load_file == 'y' || load_file == 'Y')
    {
        current_options.game_rules = input_rule_set();
    }
    else
    {
        current_options.game_rules = BASE_RULES;
    }

    return current_options;
}

/**
* Checks if the Input is valid
**/
int validate_input(struct options current_options)
{
    if
    (
        (current_options.height <= 2 || current_options.width <= 2) ||
        (current_options.alive == current_options.dead) ||
        (current_options.iterations_per_second < 1 || current_options.iterations_per_second > 10) ||
        (current_options.game_rules.min_revive > 8 || current_options.game_rules.min_survive > 8) ||
        (current_options.game_rules.max_revive > 8 || current_options.game_rules.max_survive > 8)
    )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 *  Creates an empty play field initialized with random cells
 **/
void create_field(struct options current_options, int field[][current_options.width])
{
    int field_generation;

    clear_screen();
    build_frame(80, 20);

    set_cursor(10, 5);
    printf("Load a save file [1] or generate random field [2]");

    set_cursor(5, 6);
    printf("Method: ");
    scanf("%i", &field_generation);
    fflush(stdin);

    if (field_generation == 1)
    {
        load_field(current_options, field);
    }
    else
    {
        int i, j;

        // Initialize randomizer
        time_t t;
        srand(time(&t));


        for(i = 0; i < current_options.height; i++)
        {
            for(j = 0; j < current_options.width; j++)
            {
                // Fill field based on a coin flip principle
                if (rand() % 2 == 0)
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
void print_field(struct options current_options, int field[][current_options.width], int iteration)
{
    clear_screen();

    printf("Iteration: %i\tPer second: %i \tMode: %c \n\n", iteration, current_options.iterations_per_second, current_options.mode);

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
    build_frame(80, 20); // Create an empty frame for the start menu

    set_cursor(10, 5);
    printf("Please enter custom game rules.");

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

/**
 *  Compares current state with the comparable state to determine if the game is "won"
 **/
int has_won(struct options current_options, int current_state[][current_options.width], int compare_state[][current_options.width])
{
    int i, j;
    for (i = 0; i < current_options.height; i++)
    {
        for (j = 0; j < current_options.width; j++)
        {
            if (current_state[i][j] != compare_state[i][j])
            {
                return 0;
            }
        }

    }

    return 1;
}

/**
 *  Calculate the next iteration based on the current field and rule set
 **/
void calculate_next_step(struct options current_options, int field[][current_options.width], int next_field[][current_options.width])
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
                if(count_alive > current_options.game_rules.max_survive || count_alive < current_options.game_rules.min_survive)
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
                if(count_alive > current_options.game_rules.max_revive || count_alive < current_options.game_rules.min_revive)
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

/**
 *  Exports the current field to a .gol file.
 *  This is basically a text file, so you can easily create your own save state
 **/
void save_field(struct options current_options, int field[][current_options.width])
{
    clear_screen();
    build_frame(80, 20);

    char save_name[10];

    do {
        set_cursor(5, 6);
        printf("Please enter a save name (max 10 characters): ");
        scanf("%s", save_name);
        fflush(stdin);
        if (strlen(save_name) > 10)
        {
            clear_screen();
            build_frame(80, 20);
            set_cursor(5, 4);
            printf("Name is to long.");
        }
    } while(strlen(save_name) > 10);

    char file_name[14];
    strcpy(file_name, save_name);
    strcat(file_name, ".gol");
    FILE *save_file;
    save_file = fopen(file_name, "w+");

    int i, j;
    for(i = 0; i < current_options.height; i++)
    {

        for(j = 0; j < current_options.width; j++)
        {
            //Checks if cell is dead
            fprintf(save_file, "%d", field[i][j]);

        }
        fprintf(save_file, "\n");
    }

    fclose(save_file);
}

/**
 *  Loads a .gol file into the game, with your currently set options
 **/
void load_field(struct options current_options, int field[][current_options.width])
{
    clear_screen();
    build_frame(80, 20);


    FILE *save_file = NULL;

    do {

        char file_path[256];
        set_cursor(5, 6);
        printf("Please enter a file path to a .gol file: ");
        scanf("%s", file_path);
        fflush(stdin);

        int dot_index = strlen(file_path) - 4;

        if (dot_index < 0 ||
            (file_path[dot_index] != '.'
             && file_path[dot_index + 1] != 'g'
             && file_path[dot_index + 2] != 'o'
             && file_path[dot_index + 3] != 'l'))
        {
            clear_screen();
            build_frame(80, 20);
            set_cursor(5, 4);
            printf("Invalid file type. Please select a valid file!");
            continue;
        }

        save_file = fopen(file_path, "r");
        if (save_file == NULL)
        {
            clear_screen();
            build_frame(80, 20);
            set_cursor(5, 4);
            printf("File does not exist. Please select a valid file!");
        }
    }while(save_file == NULL);

    char buffer[30];

    int i = 0;
    while (fscanf(save_file, "%[01]\n", buffer) != EOF)
    {
        int j, width = strlen(buffer);
        for (j = 0; j < width; j++)
        {
            field[i][j] = buffer[j] - '0';
        }
        i++;
    }

    fclose(save_file);
}
