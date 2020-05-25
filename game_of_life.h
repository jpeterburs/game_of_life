#ifndef GAME_OF_LIFE_H_INCLUDED
#define GAME_OF_LIFE_H_INCLUDED

struct options
{
    int height;
    int width;
    char alive;
    char dead;
    int iterations_per_second;
};

struct options start_menu();
void create_field(struct options current_options, int field[][current_options.width]);
void print_field(struct options current_options, int field[][current_options.width]);

#endif // GAME_OF_LIFE_H_INCLUDED
