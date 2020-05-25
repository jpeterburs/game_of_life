#include <stdio.h>
#include <stdlib.h>
#include "console_helper.h"
#include "game_of_life.h"

int main()
{
    // Start menu for selection of options
    struct options current_options = start_menu();

    // Debug print for list of options
    set_cursor(5, 20);
    printf("[%ix%i] %iIPS: %c %c", current_options.height, current_options.width, current_options.iterations_per_second, current_options.alive, current_options.dead);

    return 0;
}
