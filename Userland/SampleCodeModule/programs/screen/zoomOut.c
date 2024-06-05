#include <zoomOut.h>
#include <UserSyscalls.h>
#include <shell.h>

int zoomOut(int argc, char *argv[])
{
    call_clear_screen();
    call_zoomOut();
    showScreen();

    return 0;
}