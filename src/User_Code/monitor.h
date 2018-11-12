#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <ctype.h>
#include <linux/limits.h>

#include "loader.h"
#include "log.h"

#define HIJACKED_SYSCALL __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"

struct process process_List[512];

static int kill_Process(pid_t pid,char * name);

static unsigned long syscall_get_Process_Info();

static void print_Process_List(pid_t length);