#include <test_util.h>
#include <stdint.h>
#include <UserSyscalls.h>


#define MINOR_WAIT 1000000  
#define WAIT  10000000       

#define TOTAL_PROCESSES 5
#define LOWEST 1
#define MEDIUM 2
#define HIGHEST 3
int fileds[2] = {0, 0};
size_t heap_stacks[2] = {0x0000000000001000, 0x0000000000001000};

int64_t prio[TOTAL_PROCESSES] = {LOWEST, MEDIUM, HIGHEST, MEDIUM, LOWEST};
void endless_loop_print(){
  int pid = call_get_pid();

  int wait = 100000000;

  while (1){
    own_printf("%d ", pid);
    bussy_wait(wait);
  }
}
void * get_test_prio(){
  return &test_prio;
}

void test_prio(){
  int64_t pids[TOTAL_PROCESSES];
  uint64_t i;

  for (i = 0; i < TOTAL_PROCESSES; i++)
    pids[i] = call_create_process("print_loop", 0, heap_stacks, endless_loop_print, NULL, fileds);

  bussy_wait(WAIT);
  own_printf("\nCHANGING PRIORITIES...\n");
  for (i = 0; i < TOTAL_PROCESSES; i++)
    call_nice(pids[i], prio[i]);

  bussy_wait(WAIT);
  own_printf("\nBLOCKING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    call_block(pids[i]);

  own_printf("CHANGING PRIORITIES WHILE BLOCKED...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    call_nice(pids[i], MEDIUM);
  own_printf("UNBLOCKING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    call_block(pids[i]);
  bussy_wait(WAIT);
  own_printf("\nKILLING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    call_force_kill(pids[i]);

  own_printf("\nTest ended. Processes were not printed because\n");
  own_printf("they were created at background.\n");
}