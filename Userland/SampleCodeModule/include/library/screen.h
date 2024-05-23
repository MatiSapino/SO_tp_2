#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <UserSyscalls.h>

void putCursor();
void removeCursor();
void setFontSize(int size);
void putCharColorPos(char character, int color, int x, int y);
void putSquare(int x, int y, int size, int color);

#endif