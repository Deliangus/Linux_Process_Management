#include "monitor.h"


static unsigned long syscall_get_Process_Info(void)
{
    printf("..........Getting list of processes");

    unsigned long process_count = syscall(HIJACKED_SYSCALL,&process_List);
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

static void print_Process_List(unsigned long length)
{
    printf("List Length:%xl\n",length);

    for(int i = 1;i<length;i++)
    {
        printf("\t%xl\t%s\n",process_List[i].pid,process_List[i].name);
    }
    
    return;
}

static int kill_Process(unsigned long pid)
{
    
}