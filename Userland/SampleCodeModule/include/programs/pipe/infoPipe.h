#ifndef _INFO_PIPE
#define _INFO_PIPE_

#include <std_io.h>
#include <string_s.h>
#include <std_lib.h>
#include <pipe.h>

#define MAX_PIPES 32

void info_pipe(char *name);
int info_all_pipes(int argc, char *argv[]);

#endif