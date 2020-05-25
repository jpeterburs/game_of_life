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

#endif // GAME_OF_LIFE_H_INCLUDED
