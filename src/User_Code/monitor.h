#include <sys/syscall.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "loader.h"
#include "log.h"
#include "../Kernal_Module/syscall.c"
#include "../data_type.h"

#define HIJACKED_SYSCALL __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"
#define ulong unsigned long

static struct process process_List[512];

static int kill_Process(unsigned long pid,char * name);

static unsigned long syscall_get_Process_Info();

static void print_Process_List(unsigned long length);