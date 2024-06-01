#include <irqDispatcher.h>

static void int_20();
static void int_21();
static int int_80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
	switch (irq)
	{
	case 0:
		int_20();
		break;
	case 1:
		int_21();
		break;
	case 96:
		int_80(rdi, rsi, rdx, rcx, r8, r9);
		break;
	default:
		return;
		return;
	}
}

void int_20()
{
	timer_handler();
}

void int_21()
{
	keyboard_handler();
}

// handles syscalls and recieves the syscall number and registers at that instant
int int_80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{

	switch (rdi)
	{
	case 1:
		sys_write((char *)rsi, rdx, rcx);
		break;

	case 2:
		sys_read((char *)rsi, rdx, rcx);
		break;

	case 3:
		TimeClock((char *)rsi);
		break;

	case 4:
		printReg();
		break;

	case 5:
		changeSize(-1);
		break;

	case 6:
		changeSize(1);
		break;

	case 7:
		sleepms(rsi);
		break;

	case 8:
		clear();
		break;
	case 9:
		drawCursor();
		break;
	case 10:
		deleteCursor();
		break;
	case 11:
		clearScreen();
		break;
	case 12:
		getBufferPosition((int *)rsi);
		break;
	case 13:
		getLastKey((char *)rsi, rdx);
		break;
	case 14:
		setSize(rsi);
		break;
	case 15:
		putCharInSetSpace(rsi, rdx, rdx, rcx);
	case 16:
		beep(rsi);
		break;
	case 17:
		drawSquareInSetPosition(rsi, rdx, rcx, r8);
		break;
	case 18:
		return get_mem((uint8_t *)rsi, (uint8_t *)rdx, (uint16_t)rcx);
	case 19:
		get_mem_state((int *)rsi);
		break;
	case 20:
		return (uintptr_t)malloc((size_t)rsi);
	case 21:
		free((void *)rsi);
		break;
	case 22:
		return create_pipe((char *)rsi, (int *)rdx);
	case 23:
		return open_pipe((char *)rsi, (int *)rdx);
	case 24:
		return info_pipe((char *)rsi, (pipe_info_t *)rdx);
	case 25:
		return info_all_pipes((pipe_info_t **)rsi, (unsigned int)rdx);
	case 26:
		return dup2((unsigned int)rsi, (unsigned int)rdx);
	case 27:
		sys_close((int)rsi);
		break;
	case 28:
		sys_exit((int)rsi);
		break;
	case 29:
		return (uintptr_t)sem_open((char *)rsi, (int)rdx);
	case 30:
		return sem_wait((sem_ptr)rsi);
	case 31:
		return sem_post((sem_ptr)rsi);
	case 32:
		return sem_close((sem_ptr)rsi);
	case 33:
		return get_semaphores((copy_sem_t **)rsi);
	case 34:
		return get_process_table((process_table_t *)rsi);
	case 35:
		return add_process((void *)rsi, (int)rdx, (char **)rcx);
	case 36:
		return kill_process((int)rsi);
	case 37:
		return wait_process(-1, NULL);
	case 38:
		return sys_block((int)rsi);
		break;
	case 39:
		return sys_unblock((int)rsi);
		break;
	case 40:
		return wait_process((int)rsi, (int *)rdx);
	case 41:
		return sys_get_proc_status((int)rsi);
		break;
	case 42:
		return sys_set_priority((int)rsi, (int)rdx);
		break;
	case 43:
		return sys_getpid();


	default:
		return 0;
	}
	return 0;
}