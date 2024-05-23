
#ifndef __SHELL_H__
#define __SHELL_H__

#include <utils.h>
#include <UserSyscalls.h>
#include <commands.h>
#include <buffer.h>
#include <colors.h>

int start_shell();
void putLine();
void showScreen();
void clearScreenArray();
void changeStatus();

#endif /*__SHELL_H__*/