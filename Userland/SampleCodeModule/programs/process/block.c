#include <std_io.h>
#include <process.h>
#include <string_s.h>

#define ERROR -1

int block(int argc, char *argv[]){
    if (argc < 2){
        own_printf("block: missing arguments\n");
        return -1;
    }
    if (argc > 2){
        own_printf("block: too many arguments\n");
        return -1;
    }
    int pid = satoi(argv[1]);
    if ((pid == 0 && strCompare("0", argv[1]) != 0) || pid < 0){
        own_printf("block: not a valid pid\n");
        return -1;
    }
    int status = call_get_proc_status(pid);
    switch(status){
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