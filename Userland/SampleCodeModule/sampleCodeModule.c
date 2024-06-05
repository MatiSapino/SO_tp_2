/* sampleCodeModule.c */
#include <initShell.h>
#include <help.h>
#include <type.h>
#include <std_io.h>
#include <std_lib.h>
#include <strings.h>

int main()
{
	char *args[] = {"initShell"};
    call_run(initShell, 1, args);

    return 0xDEADBEEF;
}