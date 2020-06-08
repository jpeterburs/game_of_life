#ifndef GAME_OF_LIFE_H_INCLUDED
#define GAME_OF_LIFE_H_INCLUDED

#define BASE_RULES {3, 3, 2, 3};

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
void print_field(struct options current_options, int field[][current_options.width]);
struct rule_set input_rule_set();

#endif // GAME_OF_LIFE_H_INCLUDED
