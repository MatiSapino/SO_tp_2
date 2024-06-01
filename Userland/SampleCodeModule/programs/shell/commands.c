#include <commands.h>

static char command_list[COMMAND_AMOUNT][20] = {"HELP", "TIME", "REGSTATE", "DIV0", "INVALOP", "ZOOMOUT", "ZOOMIN", "SNAKE", "CLEAR", "EXIT", "SNAKE2", "PRINTMEM", "MEM", "TESTMM", "Phylo", "TESTPROCESSES", "TESTPRIO", "TESTSYNC"};
void (*functionPointers[COMMAND_AMOUNT])(char *args[], int argCount) = {help, time, regState, div0, invalidOp, zoomOut, zoomIn, play_snake, clearScreen, exitShell, snake2, print_mem, print_mem_state, test_mm_command, phylo, test_processes_command, test_prio_command, test_sync_command};

// searches for the command by going though the array of strings and comparing
void checkCommands(char *command, char *args[], int argCount)
{
    removeLeadingTrailingSpaces(command); // deletes spaces at the beginning and end of the command
    for (int i = 0; i < COMMAND_AMOUNT; i++)
    {
        if (str_cmp(command_list[i], command) == 0)
        {
            functionPointers[i](args, argCount);
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

void regState()
{
    call_regState();
}

// prints list of commands
void help()
{
    own_printf("Command list:\n", GREEN);
    for (int i = 0; i < COMMAND_AMOUNT; i++)
    {
        own_printf(" - %s\n", command_list[i]);
    }
}

void time()
{
    char timeClock[50];
    call_timeClock(timeClock);
    own_printf("%s\n", timeClock);
}

void div0()
{
    int a = 0;
    int b = 1;
    a = b / a;
}

void invalidOp()
{
    invalidOpAsm();
}

void clearScreen()
{
    call_clear_screen();
    clearScreenArray();
}

void zoomIn()
{
    call_clear_screen();
    call_zoomIn();
    showScreen();
}

void zoomOut()
{
    call_clear_screen();
    call_zoomOut();
    showScreen();
}

void exitShell()
{
    putString("Exiting Shell", RED);
    call_sleepms(100);
    putC('.', RED);
    call_sleepms(130);
    putC('.', RED);
    call_sleepms(180);
    putC('.', RED);
    changeStatus();
}

void play_snake()
{
    start_snake();
    setFontSize(1);
}

void snake2()
{
    start_snake2();
    setFontSize(1);
}

void print_mem(char *args[], int argCount)
{
    printmem(argCount, args);
}

void print_mem_state(char *args[], int argCount)
{
    printmemstate(argCount, args);
}

void test_mm_command(char *args[], int argCount)
{
    testmm(argCount, args);
}

void phylo(){
    own_printf("Philosophers problem");
    putNewLine();
}

void test_prio_command(){
    test_prio();
}

void test_processes_command(char *args[], int argCount){
    test_processes(args, argCount);

}

void test_sync_command(char *args[], int argCount){
    test_sync(argCount, args);
}


