#include <scDispatcher.h>
#include <naiveConsole.h>
#include <syscalls.h>
#include <videoDriver.h>

int64_t syscall_dispatcher(uint64_t arg0, uint64_t arg1, uint64_t arg2,
                         uint64_t arg3, uint64_t arg4, uint64_t arg5,
                         uint64_t id) {
	switch (id)
	{
	case 1:
		return sys_read((int)arg0, (char *)arg1, arg2);
	case 2:
		return sys_write((int)arg0, (char *)arg1, arg2);
	case 3:
		sys_clear_screen();
		break;
	case 4:
		sys_exit((int)arg0);
		break;
	case 5:
		return sys_gettime((time_rtc_t *)arg0, (int)arg1);
		break;
	case 6:
		return sys_run((void *)arg0, (int)arg1, (char **)arg2);
	case 7:
		return sys_cntrl_listener((uint8_t *)arg0);
	case 8:
		sys_delete_char();
		break;
	case 9:
		return sys_kill((int)arg0);
	case 10:
		return sys_block((int)arg0);
		break;
	case 11:
		return sys_unblock((int)arg0);
		break;
	case 12:
		return sys_get_mem((uint8_t *)arg0, (uint8_t *)arg1, (uint16_t)arg2);
	case 13:
		sys_get_mem_state((int *)arg0);
		break;
	case 14:
		return sys_get_proc_status((int)arg0);
		break;
	case 15:
		return sys_set_priority((int)arg0, (int)arg1);
		break;
	case 16:
        return sys_copy_cpu_state((cpu_state_t *)arg0, (request_t)arg1);
	case 17:
		sys_focus((int)arg0);
        break;
	case 18:
        sys_sched_yield();
        break;
	case 19:
		return sys_wait();
	case 20:
		return (int64_t)sys_sem_open((char *)arg0, (int)arg1);							// casteo puede romper todo ojo
	case 21:
		return sys_sem_wait((sem_ptr)arg0);
	case 22:
		return sys_sem_post((sem_ptr)arg0);
	case 23:
		sys_close((int)arg0);
		break;
	case 24:
		return sys_create_pipe((char *)arg0, (int *)arg1);
	case 25:
		return sys_open_pipe((char *)arg0, (int *)arg1);
	case 26:
		return sys_sem_close((sem_ptr)arg0);
	case 27:
		return sys_info_pipe((char *)arg0, (pipe_info_t *)arg1);
	case 28:
		return sys_info_all_pipes((pipe_info_t **)arg0, (unsigned int)arg1);
	case 29:
		return sys_get_semaphores((copy_sem_t **)arg0);
	case 30:
		return sys_dup2((unsigned int)arg0, (unsigned int)arg1);
	case 31:
		return (int64_t)sys_malloc((size_t)arg0);							// casteo puede romper todo
	case 32:
		sys_free((void *)arg0);
		break;
	case 33:
		return sys_waitpid((int)arg0, (int *)arg1);
	case 34:
		sys_setfg((int)arg0);
		break;
	case 35:
		sys_proctable((process_table_t *)arg0);
		break;
	case 36:
		return sys_getpid();
	case 37:
		sys_sleep((int)arg0);
		break;
	case 38:
		sys_switch_screen_mode((int)arg0);
		break;
	case 39:
		newline();
		return 0;
	case 40:
		sleepms((int)arg0);
		break;
	case 41:
		return get_last_key();
	case 42:
	
	default:
		return 0;
	}
	return 0;
}