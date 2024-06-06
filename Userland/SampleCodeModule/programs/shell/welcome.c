#include <std_io.h>

int welcome(int argc, char *argv[]) {
    puts(" Main commands: ");    
    puts(" help clear ps ");
    puts(" mem sem loop ");
    puts(" nice block cat ");
    puts(" wc filter pipe ");
    puts(" Type \"help\" to list all commands. ");
    puts(" Type \"help [command]\" for more information. ");
    puts(" CTRL+C KILL PROCESS ");
    puts(" CTRL+R REG SNAPSHOT ");
    puts(" CTRL+D SEND EOF ");

    return 0;
}