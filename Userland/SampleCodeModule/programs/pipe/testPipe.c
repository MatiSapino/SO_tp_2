#include <testPipe.h>
#include <infoPipe.h>
#include <pipe.h>
#include <semaphore.h>
#include <std_io.h>
#include <ipc.h>

sem_ptr sem_shell;

void process_left()
{
    call_sem_wait(sem_shell);
    int fd[2];
    if (call_create_pipe("my_pipe", fd) == -1)
        call_open_pipe("my_pipe", fd);
    call_sem_post(sem_shell);

    call_dup2(fd[1], 1);
    call_close(fd[1]);
    call_close(fd[0]);

    own_printf("Hola mundo\nescribo otra\n");

    call_exit(0);
}

void process_right()
{
    int fd[2];
    call_sem_wait(sem_shell);
    if (call_open_pipe("my_pipe", fd) == -1)
        call_create_pipe("my_pipe", fd);
    call_sem_post(sem_shell);

    call_dup2(fd[0], 0);
    call_close(fd[0]);
    call_close(fd[1]);

    // cat();
    // filter();
    wc(0, NULL);

    call_exit(0);
}

int test_pipes(int argc, char *argv[])
{
    sem_shell = call_sem_open("shell_sem", 1);
    call_run(process_left, 0, NULL);
    call_run(process_right, 0, NULL);
    call_wait();
    call_wait();
    call_sem_close(sem_shell);

    return 0;
}