#include <regState.h>
#include <UserSyscalls.h>

int regState(int argc, char *argv[])
{
    call_regState();

    return 0;
}