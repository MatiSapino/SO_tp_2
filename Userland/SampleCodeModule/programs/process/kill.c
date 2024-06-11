// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <std_io.h>
#include <string_s.h>
#include <testUtil.h>
#include <help.h>

#define ERROR -1

int kill(int argc, char *argv[]) {
    int flag = 0;
    int pid = satoi(argv[1]);
    if (argc != 2){
        own_printf("argument amount is incorrect\n");
        flag++;
    } else{
        if (pid < 0) {
            own_printf("not a valid pid - pid must be a positive value\n\n");
            flag++;
        }
        int status = call_get_proc_status(pid);
        if (status == ERROR) {
            own_printf("process does not exist\n");
            flag++;
        }
        if (status == -2) {
            own_printf("cannot kill a terminated process\n");
            flag++;
        }
        if (pid == 0) {
            own_printf("cannot kill shell\n");
            flag++;
        } 
    }
    
    if(flag > 0){
        help_kill();
        return -1;
    }

    call_kill(pid);
  

    return 0;
}