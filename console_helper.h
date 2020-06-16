#ifndef CONSOLE_HELPER_H_INCLUDED
#define CONSOLE_HELPER_H_INCLUDED

int clear_screen();

int allow_special_chars();

int build_frame(const int width, const int height);

int set_cursor(int x, int y);

int set_color(char color);

#endif // CONSOLE_HELPER_H_INCLUDED
