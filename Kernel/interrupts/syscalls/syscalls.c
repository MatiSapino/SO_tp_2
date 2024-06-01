#include <syscalls.h>

void sys_write(char *buf, int len, int color)
{
    drawWordColor(COLORS[color], buf);
}

void sys_write_fileDescriptor(char *buf, int filedescriptor){
    // if (current_pcb->process->fw == SHELL && current_pcb->process->pid == get_process_foreground_pid()){
        switch (filedescriptor){
            case STDOUT:
                drawWordColor(GREEN, buf);
                return;
            case STDERR:
                drawWordColor(RED, buf);
                return;
            default:
                drawWordColor(RED, "Invalid file descriptor");
        }
    // } 
    // else {
    //     pipe_write(current_pcb->process->fw, buf, len);
    // }
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
