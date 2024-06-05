#include <zoomIn.h>
#include <UserSyscalls.h>
#include <shell.h>

int zoomIn(int argc, char *argv[])
{
    call_clear_screen();
    call_zoomIn();
    showScreen();

    return 0;
}