#include "monitor.h"


static unsigned long syscall_get_Process_Info(void)
{
    printf("..........Getting list of processes");

    unsigned long process_count = syscall(HIJACKED_SYSCALL,&process_List);
    if(process_count!=0)
    {
        printf("..........Failed to get list of prcesses\t%lu",process_count);
    }
    else
    {
        printf("..........Successed to get list of prcesses\t%lu",process_count);
    }

    return process_count;
}

static void print_Process_List(unsigned long length)
{
    printf("List Length:%lu\n",length);

    for(int i = 1;i<length;i++)
    {
        printf("\t%lu\t%s\n",process_List[i].pid,process_List[i].name);
    }
    
    return;
}

static int kill_Process(unsigned long pid,char * name)
{
    if(kill(pid)==0)
    {
        printf("Process\t%lu\t%s has been killed\n",pid,name);

    }
    else
    {
        printf("Failed: kill process\t%lu\t%s\n.",pid,name);
    }
}

int main(int args, char **argv)
{
    pid_t pid = fork();

    if(pid == 0)
    {
        //execve("I");
    }
    else
    {

    }
}