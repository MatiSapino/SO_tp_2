// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/* sampleCodeModule.c */
#include <help.h>
#include <shell.h>
#include <std_io.h>
#include <std_lib.h>
#include <strings.h>
#include <type.h>

#define FULLSCREEN 0

int main() {
    call_clear_screen();
    call_switch_screen_mode(FULLSCREEN);

    char *args[] = {"shell"};
    call_run(shell, 1, args);

    return 0xDEADBEEF;
}