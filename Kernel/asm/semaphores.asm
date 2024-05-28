section .text
global enter_region
global leave_region

; rdi - address of the lock variable
; rsi - semaphore index
enter_region:
    push rbp
    mov rbp, rsp

    push rdi
    push rsi







leave_region: