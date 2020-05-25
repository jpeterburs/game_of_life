#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "console_helper.h"

int allow_special_chars()
{
    system("chcp 437");
    system("cls");

    return 0;
}

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

int set_cursor(int x, int y)
{
    COORD coordinates;
    coordinates.X= x;
    coordinates.Y= y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);

    return 0;
}

int set_color(char color)
{
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );

    SetConsoleTextAttribute( hstdout, color );

    return 0;
}
