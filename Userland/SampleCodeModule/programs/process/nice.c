// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <nice.h>
#include <std_io.h>
#include <string_s.h>
#include <testUtil.h>
#include <help.h>

#define ERROR -1

int nice(int argc, char *argv[]) {
    int flag = 0;
    int pid = satoi(argv[1]);
    int priority = satoi(argv[2]);
    if (argc != 3){
        own_printf("argument amount is incorrect\n");
        flag++;
    } else {
        if (pid <= 0) {
            own_printf("not a valid pid - cannot change shell priority\n\n");
            flag++;
        }
        if (priority < 1 || priority > 10) {
            own_printf("not a valid priority - priority must be between 1-10\n\n");
            flag++;
        }
    }
    if (flag > 0){
        help_nice();
        return -1;
    }
    int ret = call_set_priority(pid, priority);
    if (ret == ERROR) {
        own_printf("nice: process does not exist\n");
    }

    return 0;
}