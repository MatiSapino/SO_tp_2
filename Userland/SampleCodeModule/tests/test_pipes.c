#include <test_util.h>
#include <stdint.h>
#include <UserSyscalls.h>
#include <commands.h>
#include <ipc.h>


void test_pipe_to_wc(){
    own_printf("First line\n");
    own_printf("Second line\n");
    own_printf("Third line\n");
    own_printf("Fourth line.");

    // print("Expected WC output = 4.");
    putC(1, GREEN);
}


void test_pipe_to_filter(){
    own_printf("MURCIELAGO");
    putC(1, GREEN);
}

void tptf_title(){
    own_printf("Creating TEST_PIPE_TO_FILTER process to write to FILTER through pipe 2...\n");
    own_printf("Creating FILTER process to read from TEST_PIPE_TO_FILTER through pipe 2...\n");
    own_printf("Input to FILTER through pipe = MURCIELAGO.\n");
    // print("Expected FILTER output = MRCLG.\n");
}

void test_pipes(){
    int pipe_id = call_pipe_create_anonymous();
    int pipe_id2 = call_pipe_create_anonymous();

    own_printf("Opening pipes...\n");

    int fd1[2] = {0, pipe_id};
    int fd2[2] = {pipe_id, 0};
    int fd3[2] = {0, pipe_id2};
    int fd4[2] = {pipe_id2, 0};
    own_printf("Setting up file descriptors...\n");


    int fd[2] = {0,0};
    size_t heap_stacks[2] = {0x0000000000001000, 0x0000000000001000};

    own_printf("Creating TEST_PIPE_TO_WC process to write to WC through pipe 1...\n");
    own_printf("Creating WC process to read from TEST_PIPE_TO_WC through pipe 1...\n");

    call_create_process("test_pipe_to_wc", 0, heap_stacks, &test_pipe_to_wc, NULL, fd1);

    int pid_wc =call_create_process("wc",1,heap_stacks, get_wc(), NULL, fd2);
    call_wait_pid(pid_wc);

    int pid_filter_title = call_create_process("tptf_title", 1, heap_stacks, &tptf_title, NULL, fd);
    
    call_wait_pid(pid_filter_title);

    int pid_filter = call_create_process("test_pipe_to_filter", 0, heap_stacks, &test_pipe_to_filter, NULL, fd3);

    call_create_process("filter",1,heap_stacks, get_filter(), NULL, fd4);
    call_wait_pid(pid_filter);
    own_printf("Expected FILTER output = MRCLG");
    return;
}
void * get_test_pipes(){
    return &test_pipes;
}