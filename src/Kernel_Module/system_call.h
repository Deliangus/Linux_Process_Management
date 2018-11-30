/*
system_call.h

Created by Yuxiang Luo on long long time ago.

Copyright @ 2018 Yuxiang Luo, Jonathan Karkour, Matt. All right reserved.
*/
#define SYS_CALL_TABLE "sys_call_table"
#define SYSCALL_NI __NR_tuxcall
#define PROCESS_LIST_HEAD "PROCESS_LIST_HEAD"
#define LENGTH_PROCESS_NAME 50
#define Kernel_Name_String "system_call"
#define Kernel_Name system_call

struct process{
	char name[LENGTH_PROCESS_NAME];
	pid_t pid;
};
