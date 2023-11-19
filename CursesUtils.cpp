//
// Created by weitnow on 11/9/23.
//

#include "CursesUtils.h"
#include <ncurses.h>

void InitializeCurses(bool noDelay)
{
    initscr();
    noecho();
    curs_set(false);

    nodelay(stdscr, noDelay);
    keypad(stdscr, true);
}

void ShutdownCurses()
{
    endwin();
}

void ClearScreen()
{
    clear();
}

void RefreshScreen()
{
    refresh();
}

int ScreenWidth()
{
    return COLS;
}

int ScreenHeight()
{
    return LINES;
}

int GetChar()
{
    return getch();
}

void DrawCharacter(int xPos, int yPos, char aCharacter)
{
    mvaddch(yPos, xPos, aCharacter);
}

void MoveCursor(int xPos, int yPos)
{
    move(yPos,xPos);
}

void DrawSprite(int xPos, int yPos, const char* sprite[], int spriteHeight, int offset)
{
    for(int h = 0; h < spriteHeight; h++)
    {
        mvprintw(yPos + h, xPos, "%s", sprite[h]);
    }
}