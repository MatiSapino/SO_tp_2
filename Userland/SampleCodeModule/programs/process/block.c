// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <my_block.h>
#include <std_io.h>
#include <string_s.h>
#include <testUtil.h>
#include <help.h> 

#define ERROR -1

int block(int argc, char *argv[]) {
    int flag = 0;
    int pid;
    if (argc != 2){
        own_printf("argument amount is incorrect\n");
        flag++;
    }
    if ((pid = satoi(argv[1])) <= 0) {
        own_printf("not a valid pid - cannot block shell\n\n");
        flag++;
    }
    if (flag > 0){
        help_block();
        return -1;
    }
    int status = call_get_proc_status(pid);
    switch (status) {
        case READY:
            call_block(pid);
            break;
        case WAITING:
            call_unblock(pid);
            break;
        case ERROR:
            own_printf("block: process does not exist\n");
            break;
        default:
            break;
    }

    return 0;
}