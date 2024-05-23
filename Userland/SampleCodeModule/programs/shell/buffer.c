#include <buffer.h>

void clearBuffer(char *buff)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buff[i] = 0;
    }
}

void read_buffer(int screenIndx, char screen[SCREEN_SIZE], char buffer[BUFFER_SIZE], int status)
{
    int i = 0;
    int end_of_buffer = 0;
    int flag = 0;
    while (i < BUFFER_SIZE)
    {
        char c = getC();
        end_of_buffer = (i == BUFFER_SIZE - 1);
        if (c == '\b')
        {
            if (i > 0 && screenIndx > 0)
            {
                i--;
                screen[screenIndx--] = 0;
                screen[screenIndx--] = 0;
            }
            else
                flag = 1;
        }
        else if (c == '\n')
        {
            removeCursor();
            putC(c, GREEN);
            buffer[i] = 0;
            if (*buffer != 0)
            {
                char *args[10];
                int argCount = parseCommand(buffer, args);
                if (argCount > 0)
                {
                    checkCommands(args[0], args, argCount);
                }
            }
            if (status)
                putLine();
            clearBuffer(buffer);
            return;
        }
        else if (c == '-')
        {
            removeCursor();
            putNewLine();
            own_printf("snapshot taken!");
            putNewLine();
            putLine();
            flag = 1;
        }
        else if (c != '-')
        {
            if (!end_of_buffer)
                buffer[i++] = c;
            else
                flag = 1;
        }
        if (!flag)
        {
            removeCursor();
            putC(c, GREEN);
            putCursor();
        }

        flag = 0;
    }
    return;
}