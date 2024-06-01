#ifndef _IPC_PROGRAMS_H
#define _IPC_PROGRAMS_H

#include <std_io.h>

#define TO_UPPER(X) ((X) - ('a' - 'A'))
#define IS_VOWEL(X)                                                    \
    (TO_UPPER(X) == 'A' || TO_UPPER(X) == 'E' || TO_UPPER(X) == 'I' || \
     TO_UPPER(X) == 'O' || TO_UPPER(X) == 'U')
#define SIZE_BUFFER 2048

void filter();
int wc(int argc, char *argv[]);
void * get_wc();
int cat(int argc, char *argv[]);

// despues mover estos
int is_vowel(char c);
void * get_filter();


#endif