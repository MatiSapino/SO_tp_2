#include <std_io.h>
#include <std_lib.h>
#include <string_s.h>
#include <stdarg.h>
#include <testUtil.h>

char getC()
{
    char c;
    call_sys_read(&c, 1, 0);
    return c;
}

void putC(char c, int color)
{
    call_sys_write(&c, 1, color);
    putIntoScreen(&c);
}

void putNewLine()
{
    putC('\n', 0);
}

void putString(char *str, int color)
{
    call_sys_write(str, 0, color); // lo escribe en el buffer nomas (creo) TESTEAR
    putIntoScreen(str);
}

void putInt(int num)
{
    putIntColor(num, GREEN);
}

void putIntColor(int num, int color)
{
    if (num < 0)
    {
        putC('-', color);
        num = -num;
    }

    int divisor = 1;
    while (num / divisor >= 10)
    {
        divisor *= 10;
    }

    while (divisor > 0)
    {
        int digit = num / divisor;
        putC('0' + digit, color);
        num %= divisor;
        divisor /= 10;
    }
}

void own_printf(const char *str, ...)
{
    va_list vl;
    int i = 0, j = 0;
    char buff[1024] = {0}, tmp[20];
    char num_buff[5];
    va_start(vl, str);
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            i++;
            int min = 0;
            int s = 0;
            while (str[i] >= '0' && str[i] <= '9')
            {
                num_buff[s] = str[i];
                s++;
                i++;
            }
            num_buff[s] = '\0';
            switch (str[i])
            {
            case 'c':
            {
                buff[j] = (char)va_arg(vl, int);
                j++;
                min++;
                break;
            }
            case 'd':
            {
                itoa(va_arg(vl, int), tmp, 10);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                min = strlen(tmp);
                break;
            }
            case 'x':
            {
                ltoa(va_arg(vl, uint64_t), tmp, 16);
                strcpy(&buff[j], tmp);
                j += strlen(tmp);
                min = strlen(tmp);
                break;
            }
            case 's':
            {
                char *src = va_arg(vl, char *);
                strcpy(&buff[j], src);
                j += strlen(src);
                min = strlen(src);
                break;
            }
            }
            while (min < satoi(num_buff))
            {
                buff[j] = ' ';
                min++;
                j++;
            }
        }
        else
        {
            buff[j] = str[i];
            j++;
        }
        i++;
    }

    putString(buff, GREEN);
    va_end(vl);
}

int own_scanf(char *format, ...)
{
    va_list args;
    va_start(args, format);
    int toRet = 0;

    while (*format != '\0')
    {

        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case 'c':
            {
                char *c = va_arg(args, char *);
                *c = getC();
                toRet++;
                break;
            }
            case 'd':
            {
                int *d = va_arg(args, int *);
                toRet += readInt(d);
                break;
            }
            case 's':
            {
                char *s = va_arg(args, char *);
                toRet += readString(s);
                break;
            }
            case 'x':
            {
                int *d = va_arg(args, int *);
                toRet += readHexInt(d);
                break;
            }
            default:
                break;
            }
        }
        format++;
    }
    va_end(args);

    return toRet;
}

int readInt(int *d)
{
    int value = 0;
    int sign = 1;
    char c = getC();

    if (c == '-')
    {
        sign = -1;
        c = getC();
    }

    while ((c != '\0') && (c >= '0' && c <= '9'))
    {
        value = (c - '0') + value * 10;
        c = getC();
    }

    *d = value * sign;
    return 1;
}

int readString(char *s)
{
    int i = 0;
    char c = getC();

    while (c != '\0' && c != '\n')
    {
        s[i++] = c;
        c = getC();
    }
    s[i] = '\0'; // null terminated
    return i;
}

int readHexInt(int *d)
{
    int value = 0;
    int sign = 1;
    char c = getC();

    if (c == '-')
    {
        sign = -1;
        c = getC();
    }

    while (c != '\0' && ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')))
    {
        if (c >= 'A' && c <= 'F')
        {
            c = c - 'A' + 10;
        }
        else
        {
            c = c - '0';
        }
        value = value * 16 + c;
        c = getC();
    }

    *d = value * sign;
    return 1;
}