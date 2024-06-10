// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <time.h>

int time(int argc, char *argv[]) {
    time_rtc_t current_time;
    call_time(&current_time, 0);
    own_printf("Current date:\n");
    own_printf("%d/%d/%d\n", (int)current_time.day, (int)current_time.month,
               (int)current_time.year);
    own_printf("Current time:\n");
    own_printf("%d:%d:%d\n", (int)current_time.hour, (int)current_time.minutes,
               (int)current_time.seconds);

    return 0;
}