#include <nice.h>
#include <std_io.h>
#include <string_s.h>
#include <testUtil.h>

#define ERROR -1

int nice(int argc, char *argv[]) {
    if (argc < 3) {
        own_printf("nice: missing arguments\n");
        return -1;
    }
    if (argc > 3) {
        own_printf("nice: too many arguments\n");
        return -1;
    }
    int pid = satoi(argv[1]);
    if ((pid == 0 && strCmp("0", argv[1]) != 0) || pid < 0) {
        own_printf("nice: not a valid pid\n");
        return -1;
    }
    int priority = satoi(argv[2]);
    int ret = call_set_priority(pid, priority);
    if (ret == ERROR) {
        own_printf("nice: process does not exist\n");
    }

    return 0;
}