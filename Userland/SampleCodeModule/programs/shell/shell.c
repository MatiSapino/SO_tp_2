#include <shell.h>

static char buffer[BUFFER_SIZE] = {0};
static char screen[SCREEN_SIZE] = {0};
int screenIndx = 0;
int status;

void welcome()
{
    char *WELCOME_MESSAGE = "Welcome to the shell\nType help to show all commands\n";
    own_printf("%s", WELCOME_MESSAGE);
}

int start_shell()
{
    welcome();
    putLine();
    status = 1;
    while (status)
    {
        read_buffer();
    }
    return 0;
}