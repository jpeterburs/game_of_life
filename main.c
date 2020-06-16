#include <stdio.h>
#include <stdlib.h>
#include "console_helper.h"
#include "game_of_life.h"

int main()
{
    // Start menu for selection of options
    struct options current_options = start_menu();
    clear_screen();

    struct rule_set base_rules = BASE_RULES;

    int field[current_options.height][current_options.width];
    int next_field[current_options.height][current_options.width];

    create_field(current_options, field);
    print_field(current_options, field);

    save_field("test\0", current_options, field);

    while(1)
    {
        char next;
        scanf("%c", &next);
        fflush(stdin);

        calculate_next_step(current_options, field, base_rules, next_field);
        copy_field(current_options, next_field, field);

        print_field(current_options, next_field);


    }

    return 0;
}
