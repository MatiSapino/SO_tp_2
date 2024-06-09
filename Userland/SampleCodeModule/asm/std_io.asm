GLOBAL call_read
GLOBAL call_write
GLOBAL call_clear_screen
GLOBAL call_exit
GLOBAL call_time
GLOBAL call_run
GLOBAL call_cntrl_listener
GLOBAL call_delete_char
GLOBAL call_kill
GLOBAL call_block
GLOBAL call_unblock
GLOBAL call_get_mem
GLOBAL call_get_mem_state
GLOBAL call_get_proc_status
GLOBAL call_set_priority
GLOBAL call_copy_cpu_state
GLOBAL call_focus
GLOBAL call_sched_yield
GLOBAL call_wait
GLOBAL call_sem_open
GLOBAL call_sem_wait
GLOBAL call_sem_post
GLOBAL call_close
GLOBAL call_create_pipe
GLOBAL call_open_pipe
GLOBAL call_sem_close
GLOBAL call_info_pipe
GLOBAL call_info_all_pipes
GLOBAL call_get_semaphores
GLOBAL call_dup2
GLOBAL call_malloc
GLOBAL call_free
GLOBAL call_waitpid
GLOBAL call_setfg
GLOBAL call_get_process_table
GLOBAL call_getpid
GLOBAL call_sleep_process
GLOBAL call_switch_screen_mode
GLOBAL call_new_line
GLOBAL call_sleep_ms

section .text

%macro call_to_handler 1
    mov rax, %1     ;syscall deseada
    int 80h         ;interrupcion 80
    ret
%endmacro

call_read:
    call_to_handler 1
call_write:
    call_to_handler 2
call_clear_screen:
    call_to_handler 3
call_exit:
    call_to_handler 4
call_time:
    call_to_handler 5
call_run:
    call_to_handler 6
call_cntrl_listener:
    call_to_handler 7
call_delete_char:
    call_to_handler 8
call_kill:
    call_to_handler 9
call_block:
    call_to_handler 10
call_unblock:
    call_to_handler 11
call_get_mem:
    call_to_handler 12
call_get_mem_state:
    call_to_handler 13
call_get_proc_status:
    call_to_handler 14
call_set_priority:
    call_to_handler 15
call_copy_cpu_state:
    call_to_handler 16
call_focus:
    call_to_handler 17
call_sched_yield:
    call_to_handler 18
call_wait:
    call_to_handler 19
call_sem_open:
    call_to_handler 20
call_sem_wait:
    call_to_handler 21
call_sem_post:
    call_to_handler 22
call_close:
    call_to_handler 23
call_create_pipe:
    call_to_handler 24
call_open_pipe:
    call_to_handler 25
call_sem_close:
    call_to_handler 26
call_info_pipe:
    call_to_handler 27
call_info_all_pipes:
    call_to_handler 28
call_get_semaphores:
    call_to_handler 29
call_dup2:
    call_to_handler 30
call_malloc:
    call_to_handler 31
call_free:
    call_to_handler 32
call_waitpid:
    call_to_handler 33
call_setfg:
    call_to_handler 34
call_get_process_table:
    call_to_handler 35
call_getpid:
    call_to_handler 36
call_sleep_process:
    call_to_handler 37
call_switch_screen_mode:
    call_to_handler 38
call_new_line:
    call_to_handler 39
call_sleep_ms:
    call_to_handler 40