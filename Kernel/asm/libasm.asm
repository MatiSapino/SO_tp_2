GLOBAL cpuVendor

GLOBAL rtc_time
GLOBAL set_hour12_mode
GLOBAL set_hour24_mode
GLOBAL set_decimal_mode
GLOBAL set_BCD_mode

GLOBAL outb
GLOBAL outw
GLOBAL inb
GLOBAL inw

GLOBAL xadd
GLOBAL xchg

section .text



cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

rtc_time:
	push rbp
	mov rbp , rsp
	mov [aux] , byte rdi
	mov  al , [aux]
	out 70h,al
	in al,71h
	mov rsp, rbp
	pop rbp
ret
	
set_hour12_mode:
	push rbp
	mov rbp , rsp
	mov al, 11
	out 70h,al
	in al,71h
	mov ah,2
	not ah
	and al,ah
	out 71h,al
	mov rsp, rbp
	pop rbp
ret

set_hour24_mode:
	push rbp
	mov rbp , rsp
	mov al, 11
	out 70h,al
	in al,71h
	mov ah,2
	or al,ah
	out 71h,al
	mov rsp, rbp
	pop rbp
ret

set_decimal_mode:
	push rbp
	mov rbp , rsp
	mov al, 11
	out 70h,al
	in al,71h
	mov ah,4
	or al,ah
	out 71h,al
	mov rsp, rbp
	pop rbp
ret

set_BCD_mode:
	push rbp
	mov rbp , rsp
	mov al, 11
	out 70h,al
	in al,71h
	mov ah,4
	not ah
	and al,ah
	out 71h,al
	mov rsp, rbp
	pop rbp
ret

inb:				; Funciones para el correcto funcionamiento del soundDriver
    xor rax, rax
	mov rdx,rdi
    in al,dx		; pasaje en 8 bits
	ret

outb:
	mov     rdx, rdi
    mov     rax, rsi
	out dx, al		; pasaje en 8 bits
	ret

xadd:
	mov rax, rsi
	lock xadd [rdi], eax
	ret

xchg:
	mov rax, rsi
	xchg [rdi], eax
	ret

inw:
	xor rax, rax
    mov rdx, rdi
    in ax, dx
	ret

outw:
	mov rdx, rdi
    mov rax, rsi
    out dx, ax
	ret

section .bss
aux resb 1