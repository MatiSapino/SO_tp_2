#include <std_io.h>
#include <utils.h>
#include <string_s.h>
#include <process.h>

#define ERROR -1

int kill(int argc, char *argv[]) {
    if (argc < 2) {
        own_printf("kill: missing arguments\n");
        return -1;
    }
    if (argc > 2) {
        own_printf("kill: too many arguments\n");
        return -1;
    }
    int pid = satoi(argv[1]);
    if ((pid == 0 && strCompare("0", argv[1]) != 0) || pid < 0) {
        own_printf("kill: not a valid pid\n");
        return -1;
    }
    int status = call_get_proc_status(pid);
    if (status == ERROR) {
        own_printf("kill: process does not exist\n");
        return -1;
    } else {
        call_kill(pid);
    }

    return 0;
}