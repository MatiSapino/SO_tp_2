#include <commands.h>

static char command_list[COMMAND_AMOUNT][8] = {"HELP", "TIME", "REGSTATE", "DIV0", "INVALOP", "ZOOMOUT", "ZOOMIN", "SNAKE", "CLEAR", "EXIT", "SNAKE2", "PRINTMEM", "MEM", "TESTMM"};
void (*functionPointers[COMMAND_AMOUNT])(char *args[], int argCount, int status) = {help, time, regState, div0, invalidOp, zoomOut, zoomIn, play_snake, clearScreen, exitShell, snake2, print_mem, print_mem_state, test_mm};

// searches for the command by going though the array of strings and comparing
void checkCommands(char *command, char *args[], int argCount, int status)
{
    removeLeadingTrailingSpaces(command); // deletes spaces at the beginning and end of the command
    for (int i = 0; i < COMMAND_AMOUNT; i++)
    {
        if (strCompare(command_list[i], command) == 0)
        {
            functionPointers[i](args, argCount, status);
            return;
        }
    }
    commandNotFound(command);
}

void commandNotFound(char *command)
{
    own_printf("ERROR: - '%s' is not a valid command\n", command);
    own_printf("Type help to show all commands\n", GREEN);
}

void regState(char *args[], int argCount, int status)
{
    call_regState();
}

// prints list of commands
void help(char *args[], int argCount, int status)
{
    own_printf("Command list:\n", GREEN);
    for (int i = 0; i < COMMAND_AMOUNT; i++)
    {
        own_printf(" - %s\n", command_list[i]);
    }
}

void time(char *args[], int argCount, int status)
{
    char timeClock[50];
    call_timeClock(timeClock);
    own_printf("%s\n", timeClock);
}

void div0(char *args[], int argCount, int status)
{
    int a = 0;
    int b = 1;
    a = b / a;
}

void invalidOp(char *args[], int argCount, int status)
{
    invalidOpAsm();
}

void clearScreen(char *args[], int argCount, int status)
{
    call_clear_screen();
    clearScreenArray();
}

void zoomIn(char *args[], int argCount, int status)
{
    call_clear_screen();
    call_zoomIn();
    showScreen();
}

void zoomOut(char *args[], int argCount, int status)
{
    call_clear_screen();
    call_zoomOut();
    showScreen();
}

void changeStatus(int status)
{
    status = 0;
}

void exitShell(char *args[], int argCount, int status)
{
    putString("Exiting Shell", RED);
    call_sleepms(100);
    putC('.', RED);
    call_sleepms(130);
    putC('.', RED);
    call_sleepms(180);
    putC('.', RED);
    changeStatus(status);
}

void play_snake(char *args[], int argCount, int status)
{
    start_snake();
    setFontSize(1);
}

void snake2(char *args[], int argCount, int status)
{
    start_snake2();
    setFontSize(1);
}

void print_mem(char *args[], int argCount, int status)
{
    printmem(argCount, args);
}

void print_mem_state(char *args[], int argCount, int status)
{
    printmemstate(argCount, args);
}

void test_mm(char *args[], int argCount, int status)
{
    testmm(argCount, args);
}