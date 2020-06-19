#ifndef GAME_OF_LIFE_H_INCLUDED
#define GAME_OF_LIFE_H_INCLUDED

#define BASE_RULES (struct rule_set){3, 3, 2, 3};


struct rule_set
{
    int min_revive;
    int max_revive;
    int min_survive;
    int max_survive;
};

struct options
{
    int height;
    int width;
    char alive;
    char dead;
    int iterations_per_second;
    char mode; //'a' or 'A' for automatic mode, 'm' or 'M' for manual mode
    struct rule_set game_rules;
};


struct options start_menu();
int has_won(struct options current_options, int current_state[][current_options.width], int compare_state[][current_options.width]);
void create_field(struct options current_options, int field[][current_options.width]);
void copy_field(struct options current_options, int source_field[][current_options.width], int target_field[][current_options.width]);
void print_field(struct options current_options, int field[][current_options.width], int iteration);
struct rule_set input_rule_set();
void calculate_next_step(struct options current_options, int field[][current_options.width], int next_field[][current_options.width]);
void load_field(struct options current_options, int field[][current_options.width]);
void save_field(struct options current_options, int field[][current_options.width]);
void start_game();
int validate_input(struct options);

#endif // GAME_OF_LIFE_H_INCLUDED
