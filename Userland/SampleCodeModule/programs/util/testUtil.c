// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <process.h>
#include <std_io.h>
#include <testUtil.h>
#include <mem.h> 

// Random
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

// Memory
uint8_t memcheck(void *start, uint8_t value, uint32_t size) {
    uint8_t *p = (uint8_t *)start;
    uint32_t i;

    for (i = 0; i < size; i++, p++)
        if (*p != value)
            return 0;

    return 1;
}

size_t strlen_custom(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char * concat(const char* str1, const char* str2) {
    char* result;
    // Find the length of the input strings
    size_t len1 = strlen_custom(str1);
    size_t len2 = strlen_custom(str2);
    result = call_malloc(sizeof(char)*(len1+len2));
    // Copy the first string to the result
    for (size_t i = 0; i < len1; i++) {
        result[i] = str1[i];
    }

    // Append the second string to the result
    for (size_t i = 0; i < len2; i++) {
        result[len1 + i] = str2[i];
    }

    // Null-terminate the concatenated string
    result[len1 + len2] = '\0';
    return result;
}

// Parameters
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

// Dummies
void bussy_wait(uint64_t n) {
    uint64_t i;
    for (i = 0; i < n; i++)
        ;
}

void endless_loop() {
    int wait = 100000;
    while (1){
        bussy_wait(wait);
    }
}

void endless_loop_print(uint64_t wait) {
    int64_t pid = call_getpid();

    while (1) {
        own_printf("%d ", pid);
        bussy_wait(wait);
    }
}