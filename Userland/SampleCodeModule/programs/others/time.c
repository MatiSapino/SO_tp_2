#include <time.h>
#include <UserSyscalls.h>
#include <std_io.h>

int time(int argc, char *argv[])
{
    char timeClock[50];
    call_timeClock(timeClock);
    own_printf("%s\n", timeClock);

    return 0;
}