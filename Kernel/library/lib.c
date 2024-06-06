#include <lib.h>

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

char *strcat(char *destination, const char *source) {
    // make `ptr` point to the end of the destination string
    char *ptr = destination + strlen(destination);

    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
    }

    // null terminate destination string
    *ptr = '\0';

    // the destination is returned by standard `strcat()`
    return destination;
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

int strcmp(const char *str1, const char *str2)
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

void *memcpy(void *destination, const void *source, uint64_t length)
{
	/*
	 * memcpy does not support overlapping buffers, so always do it
	 * forwards. (Don't change this without adjusting memmove.)
	 *
	 * For speedy copying, optimize the common case where both pointers
	 * and the length are word-aligned, and copy word-at-a-time instead
	 * of byte-at-a-time. Otherwise, copy by bytes.
	 *
	 * The alignment logic below should be portable. We rely on
	 * the compiler to be reasonably intelligent about optimizing
	 * the divides and modulos out. Fortunately, it is.
	 */
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *)destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t *d = (uint8_t *)destination;
		const uint8_t *s = (const uint8_t *)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void *memset(void *destination, int32_t c, uint64_t length)
{
    uint8_t chr = (uint8_t)c;
    char *dst = (char *)destination;

    while (length--)
        dst[length] = chr;

    return destination;
}

int puts(const char *str) {
    size_t length = strlen(str);
    char new_str[length + 2];
    int i;
    for (i = 0; i < length; i++) {
        new_str[i] = str[i];
    }
    new_str[i++] = '\n';
    new_str[i] = '\0';
    return sys_write(STDOUT, new_str, length + 1);
}

char *itoa(int num, char *str, int base)
{
    int i = 0;
    int isNegative = 0;

    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }

    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    reverse(str, i);

    return str;
}

int printf(char *str, ...) {
    va_list vl;
    int i = 0, j = 0;
    char buff[100] = {0}, tmp[20];
    va_start(vl, str);
    while (str && str[i]) {
        if (str[i] == '%') {
            i++;
            switch (str[i]) {
                case 'c': {
                    buff[j] = (char)va_arg(vl, int);
                    j++;
                    break;
                }
                case 'd': {
                    itoa(va_arg(vl, int), tmp, 10);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 'x': {
                    itoa(va_arg(vl, int), tmp, 16);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 's': {
                    char *src = va_arg(vl, char *);
                    strcpy(&buff[j], src);
                    j += strlen(src);
                    break;
                }
            }
        } else {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    sys_write(1, buff, j);
    va_end(vl);
    return j;
}