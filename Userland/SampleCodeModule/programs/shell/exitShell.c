#include <exitShell.h>
#include <colors.h>
#include <std_io.h>
#include <UserSyscalls.h>
#include <shell.h>

int exitShell(int argc, char *argv[])
{
    putString("Exiting Shell", RED);
    call_sleepms(100);
    putC('.', RED);
    call_sleepms(130);
    putC('.', RED);
    call_sleepms(180);
    putC('.', RED);
    changeStatus();

    return 0;
}