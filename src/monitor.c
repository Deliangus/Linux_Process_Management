#include "monitor.h"

static unsigned long syscall_get_Process_Info(void)
{
    printf("..........Getting list of processes");

    ulong process_count = syscall(HIJACKED_SYSCALL,&process_Listh);
    if(process_count!=0)
    {
        printf("..........Failed to get list of prcesses\t%xl",process_count);
    }
    else
    {
        printf("..........Successed to get list of prcesses\t%xl",process_count);
    }

    return process_count;
}

static void print_Process_List(void)
{
    
}

int kill_Process(int pid)
{

}