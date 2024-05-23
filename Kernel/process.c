#include <memory_manager.h>
#include <process.h>

#define P_INIT_EFLAGS 0x202
#define P_INIT_CS     0x8
#define P_SS          0
#define P_EXIT_CODE   0

//static int last_pid = 0;