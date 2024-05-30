#include <process.h>
#include <interrupts.h>
#include <scheduler.h>
#include <../include/pipe/pipe.h>

static void start(function_t function, int argc, char *argv[]) {
    int status = function(argc, argv);
    kill_current_process(status);
}

static int search_by_pid(void *process, void *pid) {
    return ((process_ptr)process)->pid == *((pid_t *)pid);
}

static char **get_argv_copy(int argc, char *argv[]) {
    if (argc == 0 || argv == NULL) return NULL;

    char **argv_copy = mem_alloc(argc * sizeof(char *));
    for (size_t i = 0; i < argc; i++) {
        argv_copy[i] = mem_alloc(strlen(argv[i]) + 1);
        strcpy(argv_copy[i], argv[i]);
    }

    return argv_copy;
}

static context_ptr get_init_context(process_ptr process, function_t main, int argc, char *argv[]) {
    context_ptr context =
        (context_ptr)((uint64_t)process + K_PROCESS_STACK_SIZE -
                      sizeof(context_t));

    context->rdi = (uint64_t)main;
    context->rsi = (uint64_t)argc;
    context->rdx = (uint64_t)argv;
    context->rip = (uint64_t)&start;

    context->cs = P_INIT_CS;
    context->eflags = P_INIT_EFLAGS;
    context->ss = P_SS;

    context->rsp = (uint64_t)context;

    return context;
}

// process_ptr new_process(function_t main, int argc, char *argv[]) {
//     process_ptr process = (process_ptr )mem_alloc(sizeof(process_t));
//     if (process == NULL)
//         return NULL;

    // process->argv = get_argv_copy(argc, argv);
//     process->argc = argc;

//     process->pid = last_pid++;
//     process->priority = LOWEST;

//     process->status = READY;
    // process->exit_status = -1;
  
    // process->channel = NULL;
//     process->parent = NULL;
    // process->children = new_linked_list((int (*)(void *, void *))search_by_pid);

    // process->context = get_init_context(process, main, process->argc, process->argv);

    // /* Creates stdin in dataDescriptor 0*/
    // process->data_descriptors[0] = create_dataDescriptor(STD_T, READ_MODE);

    // /* Creates stdout in dataDescriptor 0*/
    // process->data_descriptors[1] = create_dataDescriptor(STD_T, WRITE_MODE);

    // process->dataD_index = 2;

//     return process;
// }

void set_p_params(process_ptr process, uint16_t pid, uint16_t parent_pid,
				 function_t main, int argc, char *argv[], char *name,
				 uint8_t priority, int is_init, int16_t fds[]) {
	
    process->pid = pid;
	process->parent_pid = parent_pid;
    process->argv = get_argv_copy(argc, argv);
	process->name = mem_alloc(strlen(name) + 1);
	strcpy(process->name, name);
    process->context = get_init_context(process, main, process->argc, process->argv);
	process->priority = priority;
	void *stack_end = (void *) ((uint64_t) process->stack_base + K_PROCESS_STACK_SIZE);
	process->stack_position = init_stack_frame(&start, main, stack_end, (void *) process->argv);
	process->status = READY;
    process->zombies = new_linked_list((int (*)(void *, void *))search_by_pid);
    process->is_init = is_init;

    process->fread = fds[STDIN];
    process->fwrite = fds[STDOUT];
    process->ferror = fds[STDERR];
}

void free_process(process_ptr process) {
    free_list(process->zombies);
    free(process->name);

    // free arguments
    if (process->argc) {
        for (size_t i = 0; i < process->argc; i++)
            free(process->argv[i]);

        free(process->argv);
    }

    free(process);
}

void close_fds(process_ptr process){
    // close fds in pipe.c
    // close_pipe_for_p(process->pid, process->fread)
    // close_pipe_for_p(process->pid, process->fwrite)
    // close_pipe_for_p(process->pid, process->ferror)
}

psnapshot_ptr load_snapshot(psnapshot_ptr snapshot, process_ptr process) {
	snapshot->name = mem_alloc(strlen(process->name) + 1);
	strcpy(snapshot->name, process->name);
	snapshot->pid = process->pid;
	snapshot->parentPid = process->parent_pid;
	snapshot->stackBase = process->stack_base;
	snapshot->stackPos = process->stack_position;
	snapshot->priority = process->priority;
	snapshot->status = process->status;
	snapshot->foreground = process->fread == STDIN;
	return snapshot;
}

int is_waiting(process_ptr process, uint16_t waiting_pid) {
	return process->waiting_for_pid == waiting_pid && process->status == BLOCKED;
}

int load_zombies_snapshot(int process_index, psnapshot_t psnapshot_array[], process_ptr next_p_in_schedule) {
	list_ptr zombies = next_p_in_schedule->zombies;
	to_begin(zombies);
	while (has_next(zombies))
		load_snapshot(&psnapshot_array[process_index++], (process_ptr) next(zombies));
	return process_index;
}

