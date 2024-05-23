#include <screen.h>

void putCursor()
{
    call_cursor();
}

void removeCursor()
{
    call_delete_cursor();
}

void setFontSize(int size)
{
    call_set_font_size(size);
}

void putCharColorPos(char character, int color, int x, int y)
{
    call_put_char_in_set_position(character, color, x, y);
}

void putSquare(int x, int y, int size, int color)
{
    call_put_square(x, y, size, color);
}

void putIntoScreen(char *str, int screenIndx, char screen[SCREEN_SIZE])
{
    while (*str != 0)
    {
        if (screenIndx < SCREEN_SIZE)
            screen[screenIndx++] = *str;
        str++;
    }
}

void clearScreenArray(char screen[SCREEN_SIZE], int screenIndx)
{
    for (int i = 0; i < SCREEN_SIZE; i++)
    {
        screen[i] = 0;
    }
    screenIndx = 0;
}

void showScreen(char screen[SCREEN_SIZE])
{
    call_sys_write(screen, 0, 0);
}

void putLine()
{
    own_printf("user > ");
    putCursor();
}