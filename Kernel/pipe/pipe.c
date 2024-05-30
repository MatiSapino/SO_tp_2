#include <../include/pipe/pipe.h>
#include <dataDescriptor.h>
#include <linkedList.h>
#include "../../Lib/include/string_s.h"

list_ptr pipe_list;

static int comparison_function(void *pipe, void *name) {
    pipe_ptr pipe_test = (pipe_ptr)pipe;
    char *name_test = (char *)name;

    return !str_cmp(pipe_test->name, name_test);
}

static int process_pipe_comparison_function(void * pid, void * other_pid){
    return (*(int *)pid) == (*(int *)other_pid);
}

// static void wakeup_helper(uint64_t channel, list_ptr blocked_list) {
//     int pid = wakeup(channel);
//     remove(blocked_list, (void *)&pid);
// }

// static void sleep_helper(uint64_t channel,list_ptr blocked_list){
//     process_t * process = get_current_process();
//     add(blocked_list,&process->pid);
//     sleep(channel);
// }

static void set_data_descriptors(pipe_ptr pipe) {

    data_descriptor_ptr readEnd = create_data_descriptor(PIPE_T, READ_MODE);
    set_pipe(readEnd, pipe);
    pipe->readopen = 1;

    data_descriptor_ptr writeEnd = create_data_descriptor(PIPE_T, WRITE_MODE);
    set_pipe(writeEnd, pipe);
    pipe->writeopen = 1;

    /**
     * TODO: Considerar si el agregado a procesos debe hacerse en la syscall y
     * que el pipe devuelva en un array los punteros a dataD
     */
    // process_t *process = get_current_process();
    // pipe_data_d[0] = process->dataD_index;
    // process->dataDescriptors[process->dataD_index++] = readEnd;
    // pipe_data_d[1] = process->dataD_index;
    // process->dataDescriptors[process->dataD_index++] = writeEnd;
}

int init_pipes() {
    pipe_list = new_linked_list(comparison_function);
    return 0;
}

pipe_ptr create_pipe(char *name, int pipe_fd[2]) {

    if (pipe_list == NULL) init_pipes();

    if (find(pipe_list, name, NULL) != NULL) {
        return NULL;
    }

    pipe_ptr my_pipe = mem_alloc(sizeof(pipe_t));
    if (my_pipe == NULL)
        return NULL;

    my_pipe->name = name;
    my_pipe->nread = 0;
    my_pipe->nwrite = 0;
    my_pipe->readopen = pipe_fd[0];
    my_pipe->writeopen = pipe_fd[1];
    my_pipe->blocked_pid = new_linked_list(comparison_function);

    add(pipe_list, my_pipe);

    set_data_descriptors(my_pipe);

    return my_pipe;
}

int open_pipe(char *name, int pipe_data_d[2]) {

    if (pipe_list == NULL)
        return -1;

    pipe_ptr pipe = (pipe_ptr) find(pipe_list, name, NULL);

    if (pipe == NULL) {
        return -1;
    }

    set_data_descriptors(pipe);

    return 0;
}

// int pipewrite(pipe_t pipe, const char *buffer, int count) {

//     if (pipe == NULL || buffer == NULL || count < 0)
//         return -2;

//     int i;
//     for (i = 0; i < count; i++) {
//         while (pipe->nwrite == pipe->nread + PIPE_SIZE) {
//             wakeup_helper((uint64_t) & pipe->nread, pipe->blocked_pid);
//             sleep_helper((uint64_t) & pipe->nwrite, pipe->blocked_pid);
//         }
//         pipe->data[pipe->nwrite++ % PIPE_SIZE] = buffer[i];
//     }
//     wakeup_helper((uint64_t) & pipe->nread, pipe->blocked_pid);

//     return i;
// }

// int piperead(pipe_t pipe, char *buffer, int count) {

//     if (pipe == NULL || buffer == NULL || count < 0)
//         return -2;

//     while (pipe->nread == pipe->nwrite) {
//         if (pipe->writeopen == 0)
//             return EOF;
//         sleep_helper((uint64_t)&pipe->nread, pipe->blocked_pid);
//     }

//     int i;
//     for (i = 0; i < count; i++) {
//         if (pipe->nread == pipe->nwrite)
//             break;
//         buffer[i] = pipe->data[pipe->nread++ % PIPE_SIZE];
//     }
//     wakeup_helper((uint64_t)&pipe->nwrite, pipe->blocked_pid);

//     if (pipe->nread == pipe->nwrite + 1)
//         return EOF;

//     return i;
// }

// void close_pipe(pipe_t pipe, int writable) {

//     if (pipe_list == NULL || pipe == NULL)
//         return;

//     if (writable) {
//         if (pipe->writeopen != 0) {
//             pipe->writeopen--;
//             wakeup_helper((uint64_t)&pipe->nread, pipe->blocked_pid);
//         }
//     } else {
//         if (pipe->readopen != 0) {
//             pipe->readopen--;
//             wakeup_helper((uint64_t)&pipe->nread, pipe->blocked_pid);
//         }
//     }

//     if (pipe->readopen == 0 && pipe->writeopen == 0 && pipe->nread > 0 &&
//         pipe->nwrite > 0) {
//         remove(pipe_list, pipe->name);
//         free_list(pipe->blocked_pid);
//         kfree(pipe);
//     }

//     to_begin(pipe_list);

//     if (!hasNext(pipe_list)) {
//         kfree(pipe_list);
//         pipe_list = NULL;
//     }

//     return;
// }

static void copy_info(pipe_ptr info, pipe_ptr pipe) {
    info->name = pipe->name;
    info->nread = pipe->nread;
    info->nwrite = pipe->nwrite;
    info->readopen = pipe->readopen;
    info->writeopen = pipe->writeopen;
    info->blocked_pid = pipe->blocked_pid;
}

int info_pipe(char *name, pipe_ptr info) {

    pipe_ptr pipe = (pipe_ptr) find(pipe_list, name, NULL);
    if (pipe == NULL) 
        return -1;

    copy_info(info, pipe);

    return 0;
}

int info_all_pipes(pipe_ptr info_arr[], unsigned int size) {

    int count = 0;

    if (pipe_list == NULL)
        return 0;

    to_begin(pipe_list);

    while (has_next(pipe_list) && count < size) {
        copy_info((pipe_ptr)next(pipe_list), info_arr[count++]);
    }

    return count;
}

void add_writer(pipe_ptr pipe) {
    pipe->nwrite++;
}

void add_reader(pipe_ptr pipe) {
    pipe->nread++;
}