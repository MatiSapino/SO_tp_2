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

void putLine()
{
    own_printf("user > ");
    putCursor();
}