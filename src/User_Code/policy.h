#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <ctype.h>
#include <linux/limits.h>

int kill_Process(char * name);

int apply_Process_Kill();

