#include <help.h>
#include <std_io.h>
#include <string_s.h>

static void formatter(char *name1, char *name2, char *name3, char *name4) {
    own_printf(" %15s    %15s    %15s    %15s\n", name1, name2, name3, name4);
}

static void help_cmds() {
    own_printf("\nAvilable commands:\n");
    formatter("clear", "time", "fibonacci", "primes");
    formatter("ps", "mem", "sem", "kill");
    formatter("nice", "block", "cat", "wc");
    formatter("filter", "pipe", "phylo", "loop");
    formatter("printmem", "divzero", "invopcode", "welcome");
    own_printf("\nTests:\n");
    formatter("testmm", "testproc", "testprio", "testsync");
    own_printf("\nOperadors:\n [c1] | [c2]     Connects a pipe between [c1] and [c2] commands.\n [c1] &          Runs command [c1] on background.\n");
    own_printf("Type \"help [command]\" for information about a specific command.\n");
}

static void help_error(char *cmd) {
    own_printf("Entry for command %s not found.\nType \"help\" to show available commands.\n",
           cmd);
}

static void help_fibonacci() {
    own_printf("\nCommand:\n     fibonacci       Prints fibonacci sequence.\n");
}

static void help_primes() {
    own_printf("\nCommand:\n    primes          Prints prime numbers.)\n");
}

static void help_time() {
    own_printf("\nCommand:\n     time            Displays system day and hour.\n");
}

static void help_divzero() {
    own_printf("\nCommand:\n    divzero         Forces divide-by-zero exception.\n");
}

static void help_inforeg() {
    puts("");
    puts("Command:");
    puts("    inforeg         Shows the last snapshot taken.");
    puts("");
    puts("Description:");
    puts("    Prints the value of CPU registers from the last snapshot taken.");
    puts("    by pressing the shortcut [CTRL] + [R], a gray animation");
    puts("    will be shown, and then the snapshot is going to be saved");
    puts("    and ready for future requests.");
    puts("");
}

static void help_invopcode() {
    puts("");
    puts("Command:");
    puts("    invopcode       Forces invalid opcode exception.");
    puts("");
}

static void help_welcome() {
    puts("");
    puts("Command:");
    puts("    welcome        The OS boot screen.");
    puts("");
}

static void help_clear() {
    puts("");
    puts("Command:");
    puts("    clear           Clears the screen.");
    puts("");
}

static void help_printmem() {
    puts("");
    puts("Command:");
    puts("    fibonacci       Prints fibonacci sequence.");
    puts("");
}

static void help_testinforeg() {
    puts("");
    puts("Command:");
    puts("    test-inforeg    Testing program for inforeg.");
    puts("");
    puts("Description:");
    puts("    Fills CPU registers with dummy values and runs in a infinite "
         "loop");
    puts("    until SIGINT. While looping, the user can take a snapshot for "
         "later use");
    puts("    with inforeg command");
    puts("Note:");
    puts("    Type \"help inforeg\" for more information.");
    puts("");
}

static void help_pipe() {
    puts("");
    puts("Operator:");
    puts("    [c1] | [c2]     Runs both [c1] and [c2] commands in split screen "
         "mode.");
    puts("");
    puts("Synopsis:");
    puts("    [c1] | [c2]");
    puts("    [c1] | [c2] [argv[0]]");
    puts("    [c1] [argv[0]] | [c2] [argv[0]]");
    puts("");
    puts("Description:");
    puts("    Extra spaces between commands, arguments and operator");
    puts("    are always ignored.");
    puts("");
}

static void help_ps(){
    own_printf("Command:\n   ps         Lists running processes with their pids\n");
}

static void help_mem(){
    own_printf("Command:\n mem          Shows memory usage status in bytes\n");
}

static void help_sem(){
    own_printf("Command:\n sem          Shows all active semaphores\n");
}

static void help_kill(){
    own_printf("Command:\n kill [pid]   Recieves a pid and kills that process\n");  
}

static void help_nice(){
    own_printf("Command:\n nice [pid] [prio]  Recieves a pid and modifies the priority of the process\n");  
}

static void help_block(){
    own_printf("Command:\n block [pid]        Recieves a pid and changes the status to waiting\n");  
}

static void help_cat(){
    own_printf("Command:\n cat [???]          Prints through stdout the file recieved\n");                       // falta revisar
}

static void help_wc(){
    own_printf("Command:\n wc [???]          Counts lines from input\n");                       // falta revisar
}
static void help_filter(){
    own_printf("Command:\n filter [???]          Filters vowels from input\n");                       // falta revisar
}
static void help_phylo(){
     own_printf("Command:\n phylo            Runs dining philosophers problem simulation\n");                       
}

static void help_loop(){
    own_printf("Command:\n loop [seconds]    Prints \"Hello World!\" in a loop for the amount of seconds written          \n");
}

int help(int argc, char *argv[]) {
    if (argc == 1)
        help_cmds();

    else if (strcmp("clear", argv[1]) == 0)
        help_clear();
    else if (strcmp("time", argv[1]) == 0)
        help_time();
    else if (strcmp("fibonacci", argv[1]) == 0)
        help_fibonacci();
    else if (strcmp("primes", argv[1]) == 0)
        help_primes();
    else if(strcmp("ps", argv[1]) == 0)
        help_ps();
    else if(strcmp("mem", argv[1]) == 0)
        help_mem();
    else if (strcmp("printmem", argv[1]) == 0)
        help_printmem();
    else if(strcmp("sem", argv[1]) == 0)
        help_sem();
    else if(strcmp("kill", argv[1]) == 0)
        help_kill();
    else if(strcmp("nice", argv[1]) == 0)
        help_nice();
    else if(strcmp("block", argv[1]) == 0)
        help_block();
    else if(strcmp("cat", argv[1]) == 0)
        help_cat();
    else if(strcmp("wc", argv[1]) == 0)
        help_wc();
    else if(strcmp("filter", argv[1]) == 0)
        help_filter();
    else if (strcmp("pipe", argv[1]) == 0)
        help_pipe();
    else if (strcmp("phylo", argv[1]) == 0)
        help_phylo();
    else if (strcmp("loop", argv[1]) == 0)
        help_loop();
    else if (strcmp("inforeg", argv[1]) == 0)
        help_inforeg();

    else if (strcmp("test-inforeg", argv[1]) == 0)
        help_testinforeg();

    else if (strcmp("divzero", argv[1]) == 0)
        help_divzero();

    else if (strcmp("invopcode", argv[1]) == 0)
        help_invopcode();

    else if (strcmp("welcome", argv[1]) == 0)
        help_welcome();

    

    else
        help_error(argv[1]);

    return 0;
}