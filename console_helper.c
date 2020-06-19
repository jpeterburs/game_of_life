/**
 *  Console Helper
 *
 *  Simplify various ways to work with the console,
 *  including the use of colors and special characters.
 *
 *  Disclaimer:
 *  The used functions run ONLY on Microsoft Windows (maybe not even all the time)
 *
 *  Author: Jonas Peterburs
 *  Created at: 2020/05/25
 **/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "console_helper.h"

/**
 *  Allows special Characters to be displayed inside the console application.
 *
 *  Example: Ä, ä, Ö, ö, Ü, ü, ß
 **/
int allow_special_chars()
{
    system("chcp 437");
    clear_screen();

    return 0;
}

/**
 *  Displays a simple frame.
 *  To add content, use the set_cursor function
 **/
int build_frame(const int width, const int height)
{
    int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
                printf("\xC9");
            else if (i == 0 && j == width-1)
                printf("\xBB");
            else if (i == height-1 && j == 0)
                printf("\xC8");
            else if (i == height-1 && j == width-1)
                printf("\xBC");
            else if (i == 0 || i == height-1)
                printf("\xCD");
            else if (j == 0 || j == width-1)
                printf("\xBA");
            else
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}

/**
 *  Clears console screen.
 **/
int clear_screen()
{
    system("cls");

    return 0;
}

/**
 *  Adds color to your console output.
 *  Color attributes are specified by TWO hexadecimal digits.
 *
 *  The first refers to the background,
 *  the second to the foreground.
 *
 *  Each digit can take one of the following values:
 *  0 = black           8 = dark gray
 *  1 = dark blue       9 = blue
 *  2 = dark green      A = green
 *  3 = blue-green      B = Cyan
 *  4 = dark red        C = red
 *  5 = Purple          D = Magenta
 *  6 = Orange          E = Yellow
 *  7 = Light gray      F = White
 *
 *  When used without arguments, it will revert to default.
 **/
int set_color(char color)
{
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hstdout, &csbi);

    SetConsoleTextAttribute(hstdout, color);

    return 0;
}

/**
 *  Sets the cursor to a specific position.
 *  This can be paired with the frame from the build_frame function.
 **/
int set_cursor(int x, int y)
{
    COORD coordinates;
    coordinates.X= x;
    coordinates.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);

    return 0;
}
