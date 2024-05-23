#include <exceptions.h>

char *ZERO_EXCEPTION_DESCRIPTION = "FATAL ERROR: Can not divide by 0";
char *OPCODE_EXCEPTION_DESCRIPTION = "FATAL ERROR: Invalid opcode";

void exceptionDispatcher(int ex, registerStructT *registers)
{
	char *msg;
	switch (ex)
	{
	case ZERO_EXCEPTION_ID:
		msg = ZERO_EXCEPTION_DESCRIPTION;
		break;
	case OPCODE_EXCEPTION_ID:
		msg = OPCODE_EXCEPTION_DESCRIPTION;
		break;
	}

	drawWordColor(RED, msg);
	newline();
	printRegisters(registers);
	drawWordColor(RED, "Press any key to continue");
	char c;
	sys_read(&c, 1, 0);
}
