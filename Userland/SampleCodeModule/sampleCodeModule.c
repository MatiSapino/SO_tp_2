/* sampleCodeModule.c */
#include <shell.h>
#include <help.h>
#include <type.h>
#include <std_io.h>
#include <std_lib.h>
#include <strings.h>

#define FULLSCREEN 0

int main()
{
    call_clear_screen();
    call_switch_screen_mode(FULLSCREEN);
    
	char *args[] = {"shell"};
    call_run(shell, 1, args);

    return 0xDEADBEEF;
}