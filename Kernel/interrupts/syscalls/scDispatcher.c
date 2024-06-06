#include <irqDispatcher.h>
#include <scheduler.h>
#include <time.h>
#include <stdint.h>
#include <defs.h>
#include <naiveConsole.h>
#include <interrupts.h>
#include <exceptions.h>
#include <registers.h>
#include <videoDriver.h>
#include <keyboard_buffer.h>
#include <lib.h>
#include <time.h>
#include <keyboard_driver.h>
#include <syscalls.h>
#include <sound_driver.h>
#include <memory_manager.h>
#include <pipe.h>
#include <dataDescriptor.h>
#include <semaphore.h>

int64_t syscall_dispatcher(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                         uint64_t arg3, uint64_t arg4, uint64_t arg5,
                         uint64_t id) {
	switch (id)
	{
	case 1:
		sys_write((char *)arg0, (int)(uintptr_t)arg1, arg2);
		break;

	case 2:
		sys_read((char *)arg0, (int)(uintptr_t)arg1, arg2);
		break;

	case 3:
		TimeClock((char *)arg0);
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
		sleepms(arg0);
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
		getBufferPosition((int *)arg0);
		break;
	case 13:
		getLastKey((char *)arg0, arg1);
		break;
	case 14:
		setSize(arg0);
		break;
	case 15:
		putCharInSetSpace(arg0, arg1, arg1, arg2);
	case 16:
		beep(arg0);
		break;
	case 17:
		drawSquareInSetPosition(arg0, arg1, arg2, arg3);
		break;
	case 18:
		return sys_get_mem((uint8_t *)arg0, (uint8_t *)arg1,
                               (uint16_t)arg2);
	case 19:
		get_mem_state((int *)arg0);
		break;
	case 20:
		return (uintptr_t)malloc((size_t)arg0);
	case 21:
		free((void *)arg0);
		break;
	case 22:
		return create_pipe((char *)arg0, (int *)arg1);
	case 23:
		return open_pipe((char *)arg0, (int *)arg1);
	case 24:
		return info_pipe((char *)arg0, (pipe_info_t *)arg1);
	case 25:
		return info_all_pipes((pipe_info_t **)arg0, (unsigned int)arg1);
	case 26:
		return dup2((unsigned int)arg0, (unsigned int)arg1);
	case 27:
		sys_close((int)arg0);
		break;
	case 28:
		sys_exit((int)arg0);
		break;
	case 29:
		return (uintptr_t)sem_open((char *)arg0, (int)arg1);
	case 30:
		return sem_wait((sem_ptr)arg0);
	case 31:
		return sem_post((sem_ptr)arg0);
	case 32:
		return sem_close((sem_ptr)arg0);
	case 33:
		return get_semaphores((copy_sem_t **)arg0);
	case 34:
		return get_process_table((process_table_t *)arg0);
	case 35:
		return sys_run((void *)arg0, (int)arg1, (char **)arg2);
	case 36:
		return kill_process((int)arg0);
	case 37:
		return wait_process(-1, NULL);
	case 38:
		return sys_block((int)arg0);
		break;
	case 39:
		return sys_unblock((int)arg0);
		break;
	case 40:
		return wait_process((int)arg0, (int *)arg1);
	case 41:
		return sys_get_proc_status((int)arg0);
		break;
	case 42:
		return sys_set_priority((int)arg0, (int)arg1);
		break;
	case 43:
		return sys_getpid();
	case 44:
		set_foreground_process((int)arg0);
		break;
	case 45:
		force_scheduler();
		break;
	case 46:
		sys_sleep((int)arg0);
		break;


	default:
		return 0;
	}
	return 0;
}