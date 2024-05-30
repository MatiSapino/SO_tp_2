#ifndef _USERSYSCALLS_H_
#define _USERSYSCALLS_H_

#include <stdint.h>
#include <stddef.h>
#include <infoPipe.h>

void call_sys_read(char *buf, int size, int fd);
void call_sys_write(char *buf, int size, int fd);

void call_timeClock(char *buf);
void call_sleepms(int mseconds);

void call_regState();

void call_zoomOut();
void call_zoomIn();
void call_clear();
void call_cursor();
void call_delete_cursor();
void call_clear_screen();
int call_getBuffPosition(int *pos);
void call_getLastKey(char *key, int pos);
void call_set_font_size(int size);
void call_beep(int freq);
void call_put_char_in_set_position(char character, int color, int x, int y);
void call_put_square(int x, int y, int size, int color);

int call_get_mem(uint8_t *address, uint8_t *buffer, size_t count);
void call_get_mem_state(int mem_state[]);
void *call_malloc(size_t size);
void call_free(void *ptr);

int call_create_pipe(char *name, int fd[2]);
int call_open_pipe(char *name, int fd[2]);
// int call_info_pipe(char *name, pipe_t *info);
// int call_info_all_pipes(pipe_t *info[], unsigned int size);
int call_dup2(unsigned int oldfd, unsigned int newfd);

void call_close(unsigned int fd);

int call_exit(int error_code);

#endif