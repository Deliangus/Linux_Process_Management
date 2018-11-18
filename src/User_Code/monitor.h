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

static int process_Kill(pid_t pid,char * name);

static void syscall_Get_Process_Info();

static void process_List_Print(pid_t length);

static void kernel_Module_Load();

static void kernel_Module_Remove();