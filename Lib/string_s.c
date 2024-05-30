#include <string_s.h>

char *strchr(const char *str, int c)
{
    while (*str)
    {
        if (*str == (char)c)
        {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}

char *strcpy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int str_cmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        char c1 = *str1;
        char c2 = *str2;

        if (c1 >= 'A' && c1 <= 'Z')
        {
            c1 += 'a' - 'A';
        }
        if (c2 >= 'A' && c2 <= 'Z')
        {
            c2 += 'a' - 'A';
        }

        if (c1 != c2)
        {
            return c1 - c2;
        }

        str1++;
        str2++;
    }

    return (*str1 - *str2);
}

void swap(char *c1, char *c2)
{
    char aux = *c1;
    *c1 = *c2;
    *c2 = aux;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        swap(str + start, str + end);
        start++;
        end--;
    }
}

size_t strlen(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

char *strtok(char *str, const char *delim)
{
    static char *last;
    if (str == NULL)
    {
        str = last;
    }

    if (str == NULL)
    {
        return NULL;
    }

    while (*str && strchr(delim, *str))
    {
        str++;
    }

    if (*str == '\0')
    {
        last = NULL;
        return NULL;
    }

    char *start = str;

    while (*str && !strchr(delim, *str))
    {
        str++;
    }

    if (*str)
    {
        *str = '\0';
        last = str + 1;
    }
    else
    {
        last = NULL;
    }

    return start;
}

int parseCommand(char *buffer, char *args[])
{
    int i = 0;
    char *token = strtok(buffer, " ");
    while (token != NULL && i < 10)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    return i;
}

void removePreviousSpaces(char *str)
{
    if (str == NULL)
    {
        return;
    }

    int indexNoSpaces = 0;
    int flag = 0;
    while (str[indexNoSpaces] == ' ' || str[indexNoSpaces] == '\t')
    {
        indexNoSpaces++;
        if (!flag)
        {
            flag = 1;
        }
    }
    if (flag)
    {
        int i = 0;
        while (str[indexNoSpaces])
        {
            str[i] = str[indexNoSpaces];
            i++;
            indexNoSpaces++;
        }
        str[i] = '\0';
    }
}

void removeEndingSpaces(char *str)
{
    if (str == NULL)
    {
        return;
    }

    int length = 0;
    int i = 0;

    while (str[i] != '\0')
    {
        length++;
        i++;
    }

    i = length - 1;

    while (i >= 0 && str[i] == ' ')
    {
        str[i] = '\0';
        i--;
    }
}

void removeLeadingTrailingSpaces(char *str)
{
    removePreviousSpaces(str);
    removeEndingSpaces(str);
}