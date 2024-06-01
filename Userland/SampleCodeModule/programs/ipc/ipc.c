#include <ipc.h>

void filter()                      // obs, no usa ni argc ni argv
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

void * get_wc(){
    return &wc;
}

int is_vowel(char c){
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
          c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void * get_filter(){
    return &filter;
}
