#include <ipc.h>

int filter(int argc, char *argv[])
{
    int16_t c;
    int i = 0;
    char buffer[SIZE_BUFFER];
    while (((c = getC()) != (int16_t)-1) && i < (SIZE_BUFFER - 2))
    {
        if (!IS_VOWEL(c))
        {
            buffer[i++] = c;
            if (c == '\n')
            {
                buffer[i] = '\0';
                own_printf("%s", buffer);
                i = 0;
            }
        }
    }

    if (i != 0)
    {
        buffer[i++] = '\n';
        buffer[i] = '\0';
        own_printf("%s", buffer);
    }

    return 0;
}

int cat(int argc, char *argv[])
{
    int16_t c;
    int i = 0;
    char buffer[SIZE_BUFFER];
    while (((c = getC()) != (int16_t)-1) && i < (SIZE_BUFFER - 2))
    {
        buffer[i++] = c;
        if (c == '\n')
        {
            buffer[i] = '\0';
            own_printf("%s", buffer);
            i = 0;
        }
    }

    if (i != 0)
    {
        buffer[i++] = '\n';
        buffer[i] = '\0';
        own_printf("%s", buffer);
    }

    return 0;
}

int wc(int argc, char *argv[])
{
    int16_t c;
    int count = 0;
    int i = 0;
    char buffer[SIZE_BUFFER];
    while (((c = getC()) != (int16_t)-1))
    {
        buffer[i++] = c;
        if (c == '\n')
        {
            count++;
            buffer[i] = '\0';
            own_printf("%s", buffer);
            i = 0;
        }
    }

    if (i != 0)
    {
        buffer[i++] = '\n';
        buffer[i] = '\0';
        own_printf("%s", buffer);
    }

    own_printf("TOTAL LINES: %d\n", count);

    return 0;
}