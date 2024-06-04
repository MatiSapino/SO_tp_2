#include <ipc.h>
#include <std_io.h>

#define TO_UPPER(X) ((X) - ('a' - 'A'))
#define IS_VOWEL(X)                                                            \
    (TO_UPPER(X) == 'A' || TO_UPPER(X) == 'E' || TO_UPPER(X) == 'I' ||         \
     TO_UPPER(X) == 'O' || TO_UPPER(X) == 'U')
#define SIZE_BUFFER 2048

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