#include <sys/wait.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <linux/limits.h>


#define HIJACKED_SYSCALL __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"
#define LENGTH_PROCESS_NAME 30

struct process{
	char name[LENGTH_PROCESS_NAME];
	pid_t pid;
};

struct process process_List[512];

char path_Root[150];

static int kill_Process(char * name);

static void syscall_Get_Process_Info();

static void process_List_Print(pid_t length);

static void kernel_Module_Load();

static void kernel_Module_Remove();