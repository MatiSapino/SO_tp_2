#include <clearScreen.h>
#include <UserSyscalls.h>
#include <shell.h>

int clearScreen(int argc, char *argv[])
{
    call_clear_screen();
    clearScreenArray();

    return 0;
}