#ifndef GAME_OF_LIFE_H_INCLUDED
#define GAME_OF_LIFE_H_INCLUDED

#define BASE_RULES {3, 3, 2, 3};

#include <string.h>

struct options
{
    int height;
    int width;
    char alive;
    char dead;
    int iterations_per_second;
};

struct rule_set
{
    int min_revive;
    int max_revive;
    int min_survive;
    int max_survive;
};

struct options start_menu();
void create_field(struct options current_options, int field[][current_options.width]);
void copy_field(struct options current_options, int source_field[][current_options.width], int target_field[][current_options.width]);
void print_field(struct options current_options, int field[][current_options.width]);
struct rule_set input_rule_set();
void calculate_next_step(struct options current_options, int field[][current_options.width], struct rule_set game_rules, int next_field[][current_options.width]);
void load_field(char file_path[]);
void save_field(char save_name[],struct options current_options, int field[][current_options.width]);

int validate_input(struct options);

#endif // GAME_OF_LIFE_H_INCLUDED
