#include <syscalls.h>

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

void sys_close(unsigned int fd)
{
    // process_t *process = get_current_process();
    // if (fd >= process->dataD_index)
    //     return;
    // close_dataDescriptor(process->dataDescriptors[fd]);
    // process->dataDescriptors[fd] = NULL;
}

void sys_exit(int status)
{
    // exit_process(status);
}
