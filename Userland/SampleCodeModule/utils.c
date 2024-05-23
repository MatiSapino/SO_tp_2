#include <utils.h>
#include <UserSyscalls.h>
#include <buffer.h>
#include <colors.h>
#include <limits.h>



char getC(){
    char c;
    call_sys_read(&c, 1, 0);
    return c;
}

void putNewLine(){
    putC('\n', 0);
}

void putC(char c, int color){
    call_sys_write(&c, 1, color);
    putIntoScreen(&c);
}

void putString(char * str, int color){
    call_sys_write(str, 0, color);              // lo escribe en el buffer nomas (creo) TESTEAR
    putIntoScreen(str);
}

int strCompare(char * str1, char * str2){   
    while (*str1 && *str2) {                       
        char c1 = *str1;
        char c2 = *str2;

        // Convert characters to lowercase for comparison
        if (c1 >= 'A' && c1 <= 'Z') {
            c1 += 'a' - 'A';
        }
        if (c2 >= 'A' && c2 <= 'Z') {
            c2 += 'a' - 'A';
        }

        if (c1 != c2) {
            return c1 - c2;
        }

        str1++;
        str2++;
    }

    // Compare the lengths of the strings
    return (*str1 - *str2);
}

void removePreviousSpaces(char *str) {
    if (str == NULL) {
        return;                 // check if NULL
    }

    // Find first index that is not a space
    int indexNoSpaces = 0;
    int flag = 0;
    while (str[indexNoSpaces] == ' ' || str[indexNoSpaces] == '\t') {
        indexNoSpaces++;
        if(!flag){
            flag = 1;
        }
    }
    if(flag){
        // Removes spaces from str
        int i = 0;
        while (str[indexNoSpaces]) {
            str[i] = str[indexNoSpaces];
            i++;
            indexNoSpaces++;
        }
        str[i] = '\0';      // NULL character at the end of string
    }
    
}

void removeEndingSpaces(char *str){
     if (str == NULL) {
        return; // Return if the input string is NULL
    }

    int length = 0;
    int i = 0;

    // Find the length of the string
    while (str[i] != '\0') {
        length++;
        i++;
    }

    i = length - 1;

    // Find the index of the last non-space character
    while (i >= 0 && str[i] == ' ') {
        str[i] = '\0';
        i--;
    }
}

void removeLeadingTrailingSpaces(char* str) {
    removePreviousSpaces(str);
    removeEndingSpaces(str);
}
    

void putInt(int num) {
    putIntColor(num, GREEN);
}

void putIntColor(int num, int color) {
    if (num < 0) {
        putC('-', color);
        num = -num;
    }

    int divisor = 1;
    while (num / divisor >= 10) {
        divisor *= 10;
    }

    while (divisor > 0) {
        int digit = num / divisor;
        putC('0' + digit, color);
        num %= divisor;
        divisor /= 10;
    }
}

void putCursor(){
    call_cursor();
}

void removeCursor(){
    call_delete_cursor();
}

void own_printf(const char *str, ...) {
    va_list vl;
    int i = 0, j = 0;
    char buff[1024] = {0}, tmp[20];
    char num_buff[5];
    va_start(vl, str);
    while (str && str[i]) {
        if (str[i] == '%') {
            i++;
            int min = 0;
            int s = 0;
            while (str[i] >= '0' && str[i] <= '9') {
                num_buff[s] = str[i];
                s++;
                i++;
            }
            num_buff[s] = '\0';
            switch (str[i]) {
                case 'c': {
                    buff[j] = (char)va_arg(vl, int);
                    j++;
                    min++;
                    break;
                }
                case 'd': {
                    itoa(va_arg(vl, int), tmp, 10);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    min = strlen(tmp);
                    break;
                }
                case 'x': {
                    ltoa(va_arg(vl, uint64_t), tmp, 16);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    min = strlen(tmp);
                    break;
                }
                case 's': {
                    char *src = va_arg(vl, char *);
                    strcpy(&buff[j], src);
                    j += strlen(src);
                    min = strlen(src);
                    break;
                }
            }
            while (min < satoi(num_buff)) {
                buff[j] = ' ';
                min++;
                j++;
            }
        } else {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    //_write(1, buff, j);
    putString(buff, GREEN);
    va_end(vl);
    //return j;
}

// void own_printf(const char * format, ...){
//     va_list args;
//     va_start(args, format);


//     while(*format != '\0'){
//         if(*format == '%'){
//             format++;

//             switch(*format){
//                 case 'c': {
//                     char c = (char)va_arg(args, int);
//                     putC(c, GREEN);
//                     break;
//                 }
//                 case 'd': {
//                     int d = (int)va_arg(args, int);
//                     putInt(d);
//                     break;
//                 }
//                 case 's': {
//                     char* s = va_arg(args, char*);
//                     putString(s, GREEN);
//                     break;
//                 }
//             }
//         } else {
//             putC(*format, GREEN);
//         }
//         format++;
//     }
// }

int own_scanf(char * format, ...){
    va_list args;
    va_start(args, format);
    int toRet = 0;

    while(*format != '\0' ){

        if(*format == '%'){
            format++; 
            switch(*format){
                case 'c': {
                    char* c = va_arg(args, char*);
                    *c = getC();
                    toRet++;
                    break;
                }
                case 'd': {
                    int* d = va_arg(args, int*);
                    toRet += readInt(d);
                    break;
                }
                case 's': {
                    char* s = va_arg(args, char*);
                    toRet += readString(s);
                    break;
                }
                case 'x': {
                    int* d = va_arg(args, int*);
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

int readInt(int* d){
    int value = 0;
    int sign = 1;
    char c = getC();

    if(c == '-'){
        sign = -1;
        c = getC();
    }

    while((c != '\0') && (c >= '0' && c <= '9')){
        value = (c - '0') + value*10;
        c = getC();
    }

    *d = value * sign;
    return 1;
}

int readString(char *s){
    int i = 0;
    char c = getC();

    while(c != '\0' && c != '\n'){
        s[i++] = c;
        c = getC();
    }
    s[i] = '\0'; //null terminated
    return i;
}


int readHexInt(int* d){
    int value = 0;
    int sign = 1;
    char c = getC();

    if(c == '-'){
        sign = -1;
        c = getC();
    }

    while(c != '\0' && ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))){
        if(c >= 'A' && c <= 'F'){
            c = c - 'A' + 10;
        }else{
            c = c - '0';
        }
        value = value * 16 + c;
        c = getC();
    }

    *d = value * sign;
    return 1;
}

void setFontSize(int size){
    call_set_font_size(size);
}

void putCharColorPos(char character, int color, int x, int y){
    call_put_char_in_set_position(character, color, x, y);
}

void putSquare(int x, int y, int size, int color){
    call_put_square(x, y, size, color);
}

long strtol(const char *nptr, char **endptr, int base) {
    const char *s;
    long acc, cutoff;
    int c;
    int neg, any, cutlim;
    /*
     * Skip white space and pick up leading +/- sign if any.
     * If base is 0, allow 0x for hex and 0 for octal, else
     * assume decimal; if base is already 16, allow 0x.
     */
    s = nptr;
    do {
        c = (unsigned char)*s++;
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else {
        neg = 0;
        if (c == '+')
            c = *s++;
    }
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    /*
     * Compute the cutoff value between legal numbers and illegal
     * numbers.  That is the largest legal value, divided by the
     * base.  An input number that is greater than this value, if
     * followed by a legal input character, is too big.  One that
     * is equal to this value may be valid or not; the limit
     * between valid and invalid numbers is then based on the last
     * digit.  For instance, if the range for longs is
     * [-2147483648..2147483647] and the input base is 10,
     * cutoff will be set to 214748364 and cutlim to either
     * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
     * a value > 214748364, or equal but the next digit is > 7 (or 8),
     * the number is too big, and we will return a range error.
     *
     * Set any if any `digits' consumed; make it negative to indicate
     * overflow.
     */
    cutoff = neg ? LONG_MIN : LONG_MAX;
    cutlim = cutoff % base;
    cutoff /= base;
    if (neg) {
        if (cutlim > 0) {
            cutlim -= base;
            cutoff += 1;
        }
        cutlim = -cutlim;
    }
    for (acc = 0, any = 0;; c = (unsigned char)*s++) {
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0)
            continue;
        if (neg) {
            if (acc < cutoff || (acc == cutoff && c > cutlim)) {
                any = -1;
                acc = LONG_MIN;
                // errno = ERANGE;
            } else {
                any = 1;
                acc *= base;
                acc -= c;
            }
        } else {
            if (acc > cutoff || (acc == cutoff && c > cutlim)) {
                any = -1;
                acc = LONG_MAX;
                // errno = ERANGE;
            } else {
                any = 1;
                acc *= base;
                acc += c;
            }
        }
    }
    if (endptr != 0)
        *endptr = (char *)(any ? s - 1 : nptr);
    return (acc);
}

int isspace(int c) {
    return c == ' ';
}

int isdigit(int c) {
    return c >= '0' && c <= '9';
}

int isalpha(int c) {
    return islower(c) || isupper(c);
}

int islower(int c) {
    return c >= 'a' && c <= 'z';
}

int isupper(int c) {
    return c >= 'A' && c <= 'Z';
}

uint8_t memcheck(void *start, uint8_t value, uint32_t size) {
    uint8_t *p = (uint8_t *)start;
    uint32_t i;

    for (i = 0; i < size; i++, p++)
        if (*p != value)
            return 0;

    return 1;
}

int64_t satoi(char *str) {
    uint64_t i = 0;
    int64_t res = 0;
    int8_t sign = 1;

    if (!str)
        return 0;

    if (str[i] == '-') {
        i++;
        sign = -1;
    }

    for (; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        res = res * 10 + str[i] - '0';
    }

    return res * sign;
}

static uint32_t m_z = 362436069;
static uint32_t m_w = 521288629;

uint32_t GetUint() {
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

uint32_t GetUniform(uint32_t max) {
    uint32_t u = GetUint();
    return (u + 1.0) * 2.328306435454494e-10 * max;
}

void *memset(void *destination, int32_t c, uint64_t length) {
    uint8_t chr = (uint8_t)c;
    char *dst = (char *)destination;

    while (length--)
        dst[length] = chr;

    return destination;
}

char *itoa(int num, char *str, int base) {
    int i = 0;
    int isNegative = 0;

    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

char *strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

size_t strlen(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *ltoa(long num, char *str, int base) {
    int i = 0;
    int isNegative = 0;

    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        swap(str + start, str + end);
        start++;
        end--;
    }
}

void swap(char *c1, char *c2) {
    char aux = *c1;
    *c1 = *c2;
    *c2 = aux;
}

char* strtok(char* str, const char* delim) {
    static char* last;
    if (str == NULL) {
        str = last;
    }

    if (str == NULL) {
        return NULL;
    }

    // Saltar delimitadores al principio
    while (*str && strchr(delim, *str)) {
        str++;
    }

    if (*str == '\0') {
        last = NULL;
        return NULL;
    }

    char* start = str;

    // Encontrar el final del token
    while (*str && !strchr(delim, *str)) {
        str++;
    }

    if (*str) {
        *str = '\0';
        last = str + 1;
    } else {
        last = NULL;
    }

    return start;
}

char* strchr(const char* str, int c) {
    while (*str) {
        if (*str == (char)c) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

void endless_loop() {
    while (1)
        ;
}