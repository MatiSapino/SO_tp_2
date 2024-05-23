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
        read_buffer(&screenIndx, screen, buffer, &status);
    }
    return 0;
}

void changeStatus()
{
    status = 0;
}

void showScreen()
{
    call_sys_write(screen, 0, 0);
}

void clearScreenArray()
{
    for (int i = 0; i < SCREEN_SIZE; i++)
    {
        screen[i] = 0;
    }
    screenIndx = 0;
}

void putIntoScreen(char *str)
{
    while (*str != 0)
    {
        if (screenIndx < SCREEN_SIZE)
            screen[screenIndx++] = *str;
        str++;
    }
}