//#include <sys/wait.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <linux/limits.h>

#include "../Kernel_Module/system_call.h"

#define HIJACKED_SYSCALL __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"
#define PATH_ROOT path_Root
#define PATH_KRN path_KRN

struct process process_List[512];

char path_Root[150];

char path_KRN[150];

static int kill_Process(char * name);

static void syscall_Get_Process_Info();

static void process_List_Print(pid_t length);

static void process_List_Print_To_File(pid_t length,char* file_path);

static void kernel_Module_Load();

static void kernel_Module_Remove();

void initialize_variables();
