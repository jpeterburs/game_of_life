#include <stdio.h>
#include <stdlib.h>
#include "game_of_life.h"

int main()
{
    struct options current_options = start_menu();

    printf("[%ix%i] %iIPS: %c %c", current_options.height, current_options.width, current_options.iterations_per_second, current_options.alive, current_options.dead);
    return 0;
}
