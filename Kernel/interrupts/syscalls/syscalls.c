#include <syscalls.h>
#include <process.h>

#define ADDRESS_LIMIT 0xFFFFFFFF

void sys_write(char *buf, int len, int color)
{
    drawWordColor(COLORS[color], buf);
}

void sys_read(char *buf, int len, int filedescriptor)
{
    int pos;
    getBufferPosition(&pos);
    char aux = 0;
    for (int i = 0; i < len;)
    {
        _hlt();
        aux = getCharAt(pos);
        if (aux > 0 && aux <= 255)
        {
            if (aux == 0x39)
                buf[i++] = ' ';
            else
                buf[i++] = aux;
            setPos(pos + 1);
        }
        getBufferPosition(&pos);
    }
}

uint16_t sys_get_mem(uint8_t *address, uint8_t *buffer, uint16_t count) {
    int i;
    for (i = 0; i < count; i++) {
        if ((uint64_t)address > ADDRESS_LIMIT) {
            return i;
        }
        buffer[i] = (*address);
        address++;
    }
    return i;
}

void sys_close(unsigned int fd)
{
    process_t *process = get_current_process();
    if (fd >= process->dataD_index)
        return;
    close_dataDescriptor(process->dataDescriptors[fd]);
    process->dataDescriptors[fd] = NULL;
}

void sys_exit(int status)
{
    exit_process(status);
}

int sys_run(void *main, int argc, char *argv[]) {
    return add_process(main, argc, argv);
}

int sys_block(int pid) {
    process_t *process = get_process(pid);
    if (process != NULL) {
        process->status = WAITING;
        return SUCCESS;
    }
    return ERROR;
}

int sys_unblock(int pid) {
    process_t *process = get_process(pid);
    if (process != NULL) {
        process->status = READY;
        return SUCCESS;
    }
    return ERROR;
}

int sys_get_proc_status(int pid) {
    process_t *process = get_process(pid);
    if (process == NULL) {
        return ERROR;
    }
    return process->status;
}

int sys_set_priority(int pid, int priority) {
    process_t *process = get_process(pid);
    if (process == NULL) {
        return ERROR;
    }

    // clamp priority value
    if (process->priority >= HIGHEST)
        process->priority = HIGHEST;
    else if (process->priority <= LOWEST)
        process->priority = LOWEST;
    else
        process->priority = priority;
    return SUCCESS;
}

int sys_getpid() {
    process_t *process = get_current_process();
    if (process == NULL)
        return -1;

    return process->pid;
}