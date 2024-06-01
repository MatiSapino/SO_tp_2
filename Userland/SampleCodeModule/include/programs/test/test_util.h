#ifndef _TEST_UTIL_H
#define _TEST_UTIL_H
#include <stdint.h>
#include <UserSyscalls.h>
#include <utils.h>

#define TEST_MAXMEM 0x100000

void tests();
uint64_t test_mm();
void test_prio();
int64_t test_processes();
uint64_t test_sync(int argc, char **argv);
void test_pipes_2();
uint32_t get_uint();
uint32_t get_uniform(uint32_t max);
int64_t satoi(char *str);
void endless_loop_print();
void * get_testmm();
void * get_test_prio();
void * get_test_processes();
void * get_test_sync();
void * get_test_pipes();
void * get_tests();
char * concat(char * str1, char * str2);

// cosas de pipes
void test_pipe_to_wc();
void test_pipe_to_filter();
void tptf_title();
void test_pipes();
void * get_test_pipes();
#endif