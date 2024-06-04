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

int strcmp(char *str1, char *str2)
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