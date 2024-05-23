GLOBAL call_sys_read
GLOBAL call_sys_write
GLOBAL call_timeClock
GLOBAL call_regState
GLOBAL call_zoomOut
GLOBAL call_zoomIn
GLOBAL call_sleepms
GLOBAL call_clear
GLOBAL call_cursor
GLOBAL call_delete_cursor
GLOBAL call_clear_screen
GLOBAL call_getBuffPosition
GLOBAL call_getLastKey
GLOBAL call_set_font_size
GLOBAL call_put_char_in_set_position
GLOBAL call_beep
GLOBAL call_put_square
GLOBAL call_get_mem
GLOBAL call_get_mem_state
GLOBAL call_malloc
GLOBAL call_free
GLOBAL call_run
GLOBAL call_wait
GLOBAL call_kill
GLOBAL call_block
GLOBAL call_unblock
GLOBAL call_getpid

section .text

%macro call_to_handler 1
    push rbp
    mov rbp, rsp
    mov r9, r8      ;arg 5
    mov r8, rcx     ;arg 4
    mov rcx, rdx    ;arg 3
    mov rdx, rsi    ;arg 2
    mov rsi, rdi    ;arg 1
    mov rdi, %1     ;syscall deseada
    int 80h         ;interrupcion 80
    mov rsp, rbp
	pop rbp
    ret
%endmacro

call_sys_write:
    call_to_handler 1
call_sys_read:
    call_to_handler 2
call_timeClock:
    call_to_handler 3
call_regState:
    call_to_handler 4
call_zoomOut:
    call_to_handler 5
call_zoomIn:
    call_to_handler 6
call_sleepms:
    call_to_handler 7
call_clear:
    call_to_handler 8
call_cursor:
    call_to_handler 9
call_delete_cursor:
    call_to_handler 10
call_clear_screen:
    call_to_handler 11
call_getBuffPosition:
    call_to_handler 12
call_getLastKey:
    call_to_handler 13
call_set_font_size:
    call_to_handler 14
call_put_char_in_set_position:
    call_to_handler 15
call_beep:
    call_to_handler 16
call_put_square:
    call_to_handler 17
call_get_mem:
    call_to_handler 18
call_get_mem_state:
    call_to_handler 19
call_malloc:
    call_to_handler 20
call_free:
    call_to_handler 21
call_run:
    call_to_handler 22
call_wait:
    call_to_handler 23
call_kill:
    call_to_handler 24
call_block:
    call_to_handler 25
call_unblock:
    call_to_handler 26
call_getpid:
    call_to_handler 27