#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <ctype.h>
#include <linux/limits.h>

void kill_Process_Single(char * name);

void eliminate_Process(char * name);

int apply_Process_Kill();

int apply_Process_Eliminate();

int update_Process_Unknown();

void execute_Kill(pid_t);

void execute_Eliminate(pid_t);
