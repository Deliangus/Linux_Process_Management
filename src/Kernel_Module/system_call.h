#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>
#include <asm/unistd.h>

#define SYS_CALL_TABLE "sys_call_table"
#define SYSCALL_NI __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"
#define LENGTH_PROCESS_NAME 30
#define Kernel_Name_String "system_call"
#define Kernel_Name system_call

struct process{
	char name[LENGTH_PROCESS_NAME];
	pid_t pid;
};
