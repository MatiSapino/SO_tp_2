#include <irqDispatcher.h> 

static void int_20();
static void int_21();
static int int_80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);


void irqDispatcher(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	switch(irq){
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

void int_20() { 
	timer_handler(); 
}

void int_21() {
	keyboard_handler();
}

// handles syscalls and recieves the syscall number and registers at that instant
int int_80(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {

    switch (rdi)
	{
	case 1:
		sys_write((char*)rsi, rdx, rcx);
		break;
	
	case 2:
		sys_read((char*)rsi, rdx, rcx);
		break;

	case 3:
		TimeClock((char*)rsi);
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
		getBufferPosition((int*)rsi);
		break;
	case 13:
		getLastKey((char*)rsi, rdx);
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
		return (uintptr_t)mem_alloc((size_t)rsi);
	case 21:
		free((void *)rsi);
		break;
	case 22:
		return 0;
	case 23:
		return 0;
	case 24:
		return 0;
	case 25:
		return 0;
	case 26:
		return 0;
	case 27:
		return 0;
	case 28:
		return 0;
	case 29:
		// call_sem_up
		//return my_sem_up((char*)rsi);
	case 30:
		// call_sem_down
		//return my_sem_down((char*)rsi);
	case 31:
		// call_sem_open
		//return my_sem_open((char*)rsi, rdx);
	case 32:
		// call_sem_close
		//return my_sem_close((char*)rsi); 
	case 33:
		// return my_get_pid(); faltaria el getpid() propio
		break;
	case 34:
		// create_process();
		break;
	case 35:
		// call_close_pipe();
		break;
	case 36:
		// call_create_process();
		break;
	case 37: 
		// call_block()
		break;
	case 38:
		// call_nice()
		break;
	case 39:
		// call_force_kill();
		break;
	case 40:
		// call_force_timer();
		break;
	case 41:
		// create_pipe_anonymous();
		break;
	case 42:
		sys_write_fileDescriptor((char*)rsi, rdx);
	default:
		return 0;
	}
	return 0;
}