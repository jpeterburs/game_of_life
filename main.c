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

    int pre_last_state[current_options.height][current_options.width];
    int last_state[current_options.height][current_options.width];

    create_field(current_options, field);

    save_field("t", current_options, field);
    int l_field[current_options.height][current_options.width];
    load_field("t.gol", current_options, l_field);
    print_field(current_options, l_field);

    char next;
    printf("\n");
    printf("Press [Enter] for next iteration.");
    scanf("%c", &next);

    while(has_won(current_options, field, pre_last_state) != 1)
    {
        print_field(current_options, field);
        calculate_next_step(current_options, field, base_rules, next_field);

        // cache last fields for state determination
        copy_field(current_options, last_state, pre_last_state);
        copy_field(current_options, field, last_state);

        copy_field(current_options, next_field, field);

        char next;
        printf("\n");
        printf("Press [Enter] for next iteration.");
        scanf("%c", &next);
        fflush(stdin);
    }

    if (has_won(current_options, field, pre_last_state))
    {
        printf("You have won! Maybe ...\n");
        return 0;
    }
    else
    {
        printf("Unable to determine state.\n");
        return 1;
    }
}
