//
// Created by weitnow on 11/9/23.
//

#ifndef TEXTINVADERS_CURSESUTILS_H
#define TEXTINVADERS_CURSESUTILS_H

#include <ncurses.h>

enum ArrowKeys
{
    AK_UP = 119,
    AK_DOWN = 115,
    AK_LEFT = 97,
    AK_RIGHT = 100
};

void InitializeCurses(bool nodelay);
void ShutdownCurses();
void ClearScreen();
void RefreshScreen();
int ScreenWidth();
int ScreenHeight();
int GetChar();
void DrawCharacter(int xPos, int yPos, char aCharacter);
void MoveCursor(int xPos, int yPos);
void DrawSprite(int xPos, int yPos, const char* sprite[], int spriteHeight, int offset = 0);

#endif //TEXTINVADERS_CURSESUTILS_H
