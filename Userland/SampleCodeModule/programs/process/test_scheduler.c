// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <test_scheduler.h>

int dummy(int argc, char *argv[]) {
    return 0;
}

int scheduler(int argc, char *argv[]) {
    char *args[] = {"dummy"};
    while (1) {
        call_run(dummy, 1, args);
        call_run(dummy, 1, args);
        call_wait();
        call_wait();
    }

    return 0;
}