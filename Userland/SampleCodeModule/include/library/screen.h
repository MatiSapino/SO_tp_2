#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <std_io.h>

#include <UserSyscalls.h>

#define SCREEN_SIZE 5000

void putCursor();
void removeCursor();
void setFontSize(int size);
void putCharColorPos(char character, int color, int x, int y);
void putSquare(int x, int y, int size, int color);
void putIntoScreen(char *str, int screenIndx, char screen[SCREEN_SIZE]);
void clearScreenArray(char screen[SCREEN_SIZE], int screenIndx);
void showScreen(char screen[SCREEN_SIZE]);
void putLine();

#endif