#include <sys/syscall.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "loader.h"
#include "log.h"
#include "syscall.c"

#define HIJACKED_SYSCALL __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"

static struct process[512] process_List;

static int kill_Process(unsigned long pid);

static unsigned long syscall_get_Process_Info();

static void print_Process_List(void);