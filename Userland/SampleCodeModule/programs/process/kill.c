// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <string_s.h>
#include <testUtil.h>
#include <help.h>

#define ERROR -1

int kill(int argc, char *argv[]) {
    int flag = 0;
    if (argc < 2) {
        own_printf("kill: missing arguments\n");
        flag++;
    }
    if (argc > 2) {
        own_printf("kill: too many arguments\n");
        flag++;
    }
    int pid = satoi(argv[1]);
    if ((pid == 0 && strcmp("0", argv[1]) != 0) || pid < 0) {
        own_printf("kill: not a valid pid\n");
        flag++;
    }
    int status = call_get_proc_status(pid);
    if (status == ERROR) {
        own_printf("kill: process does not exist\n");
        flag++;
    }
    if (status == -2) {
        own_printf("kill: cannot kill a terminated process\n");
        flag++;
    }
    if (pid == 0) {
        own_printf("kill: cannot kill shell\n");
        flag++;
    } 
    if(flag > 0){
        help_kill();
        return -1;
    }

    call_kill(pid);
  

    return 0;
}