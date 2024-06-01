#include <test_util.h>
#include <utils.h>
int filed[2] = {0, 0};
size_t heap_stack[2] = {0x0000000000001000, 0x0000000000001000};
char *argv_aux[2];
void * get_tests(){
    return &tests;
}

void tests(){
    own_printf("Available tests:\n");
    own_printf("  A - Test memory manager\n");
    own_printf("  B - Test priority\n");
    own_printf("  C - Test processes\n");
    own_printf("  D - Test synchronization\n");
    own_printf("  E - Test without synchronization\n");
    own_printf("  F - Test Pipe IPC\n");
    own_printf("  Any other key to quit\n");
    char c;
    int test_num = 0;
    c = getC();
    if (c >= 'A' && c <= 'F'){
      test_num = c - 'A' + 1;
      
    }
    else{
      own_printf("Quiting...\n");
      return;
    }


    argv_aux[0] = "3";
    argv_aux[1]= "1";
int filed1[2] = {0, 0};
    switch (test_num){
        case 1:
            call_create_process("test_mm", 1, heap_stack, get_testmm(), NULL, filed1);
            break;
        case 2:
            call_create_process("test_prio", 1, heap_stack, get_test_prio(), NULL, filed1);
            break;
        case 3:
            call_create_process("test_processes", 1, heap_stack, get_test_processes(), NULL, filed1);
            break;
        case 4:
            call_create_process("test_sync", 1, heap_stack, get_test_sync(), argv_aux, filed1);
            break;
        case 5:
            argv_aux[1] = "0";
            call_create_process("test_sync", 1, heap_stack, get_test_sync(), argv_aux, filed1);
            break;
        case 6:
            call_create_process("test_pipes", 1, heap_stack, get_test_pipes(), argv_aux, filed1);
            break;
    }
}
static uint32_t m_z = 362436069;
static uint32_t m_w = 521288629;

uint32_t get_uint(){
  m_z = 36969 * (m_z & 65535) + (m_z >> 16);
  m_w = 18000 * (m_w & 65535) + (m_w >> 16);
  return (m_z << 16) + m_w;
}

uint32_t get_uniform(uint32_t max){
  uint32_t u = get_uint();
  return (u + 1.0) * 2.328306435454494e-10 * max;
}






// }