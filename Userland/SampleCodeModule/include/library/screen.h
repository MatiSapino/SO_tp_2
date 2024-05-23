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
void putLine();

#endif