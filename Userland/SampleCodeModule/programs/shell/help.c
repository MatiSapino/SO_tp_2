// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <help.h>
#include <std_io.h>
#include <string_s.h>

char *command_names_array[100] = {
    "help",     "clear",   "time",      "fibonacci", "primes",  "ps",
    "mem",      "sem",     "kill",      "nice",    "block",
    "cat",      "wc",      "filter",    "pipe",      "phylo",   "loop",
    "printmem", "divzero", "invopcode", "welcome", "testmm", "testproc", "testprio", "testsync"};

void (*command_functions_array[100])(void) = {
    help_help,      help_clear,   help_time,    help_fibonacci,  help_primes,
    help_ps,        help_mem,    help_sem,        help_kill,
    help_nice,      help_block,   help_cat,     help_wc,         help_filter,
    help_pipe,      help_phylo,   help_loop,    help_printmem,   help_divzero,
    help_invopcode, help_welcome, help_testmm, help_testproc, help_testprio, help_testsync};

static void formatter(char *name1, char *name2, char *name3, char *name4) {
    own_printf(" %15s    %15s    %15s    %15s\n", name1, name2, name3, name4);
}

static void help_cmds() {
    own_printf("Available commands:\n");
    formatter("clear", "time", "fibonacci", "primes");
    formatter("ps", "mem", "sem", "kill");
    formatter("nice", "block", "cat", "wc");
    formatter("filter", "pipe", "phylo", "loop");
    formatter("printmem", "divzero", "invopcode", "welcome");
    own_printf("\nTests:\n");
    formatter("testmm", "testproc", "testprio", "testsync");
    own_printf(
        "\nOperadors:\n [c1] | [c2]     Connects a pipe between [c1] and [c2] "
        "commands.\n [c1] &          Runs command [c1] on background.\n");
    own_printf(
        "Type \"help [command]\" for information about a specific command.\n");
}

void help_error(char *cmd) {
    own_printf("Entry for command %s not found.\nType \"help\" to show "
               "available commands.\n",
               cmd);
}

void help_fibonacci() {
    own_printf("Command:\n     fibonacci       Prints fibonacci sequence.\n");
}

void help_primes() {
    own_printf("Command:\n    primes          Prints prime numbers.\n");
}

void help_time() {
    own_printf(
        "Command:\n     time            Displays system day and hour.\n");
}

void help_divzero() {
    own_printf(
        "Command:\n    divzero         Forces divide-by-zero exception.\n");
}


void help_invopcode() {
    own_printf(
        "Command:\n    invopcode       Forces invalid opcode exception.\n");
}

void help_welcome() {
    own_printf("Command:\n    welcome        The OS boot screen.\n");
}

void help_clear() {
    own_printf("Command:\n    clear           Clears the screen.\n");
}

void help_help() {
    own_printf("Command: \n help      displays available commands\n");
}

void help_printmem() {
    own_printf("Command:\n    printmem [Lowest memory value]      Prints memory contents from the position given.\n");
}


void help_pipe() {
    own_printf("Operator:\n    [c1] | [c2]     Runs both [c1] and [c2] "
               "commands in split screen mode.\n");
    own_printf("\nSynopsis:\n    [c1] | [c2]\n");
    own_printf("    [c1] | [c2] [argv[0]]\n");
    own_printf("    [c1] [argv[0]] | [c2] [argv[0]]\n\n");
    own_printf("Description:\n    Extra spaces between commands, arguments and "
               "operator are always ignored.\n\n");
}

void help_ps() {
    own_printf("Command:\n    ps         Lists running processes with their "
               "pids\n\n");
}

void help_mem() {
    own_printf(
        "Command:\n    mem          Shows memory usage status in bytes\n\n");
}

void help_sem() {
    own_printf("Command:\n    sem          Shows all active semaphores\n\n");
}

void help_kill() {
    own_printf(
        "Command:\n kill [pid]   Recieves a pid and kills that process\n");
}

void help_nice() {
    own_printf("Command:\n nice [pid] [prio]  Recieves a pid and modifies the "
               "priority of the process\n");
}

void help_block() {
    own_printf("Command:\n block [pid]        Recieves a pid and changes the "
               "status to waiting\n");
}

void help_cat() {
    own_printf(
        "Command:\n cat          Prints through stdout the file recieved\n");
}

void help_wc() {
    own_printf("Command:\n wc          Counts lines from input\n");
}
void help_filter() {
    own_printf("Command:\n filter          Filters vowels from input\n");
}
void help_phylo() {
    own_printf("Command:\n phylo            Runs dining philosophers problem "
               "simulation\n");
}

void help_loop() {
    own_printf("Command:\n loop [seconds]    Prints \"Hello World!\" in a loop every [seconds] amount of time          \n");
}

void help_testmm(){
    own_printf("Command:\n testmm [MB]      Tests memory manager\n");
}

void help_testproc(){
    own_printf("Command:\n testproc [process_to_create]     Creates, kills and modifies processes randomly\n");
}

void help_testprio(){
    own_printf("Command:\n testprio       Tests priorities\n");

}

void help_testsync(){
    own_printf("Command:\n testsync [inc_amount] [proc_amount] [if_uses_sem]  Tests synchronization\n");
}

int help(int argc, char *argv[]) {
    if (argc == 1) {
        help_cmds();
        return 0;
    }

    else {
        for (int i = 0; i < 100; i++) {
            if (strcmp(command_names_array[i], argv[1]) == 0) {
                command_functions_array[i]();
                return 0;
            }
        }
    }
    help_error(argv[1]);
    return 0;
}
