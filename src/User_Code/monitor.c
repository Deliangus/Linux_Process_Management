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
    char instruction [50] = "kill ";

    sprintf(instruction, "%s %ld","kill", pid);

    int shell = system(instruction);

    if(shell==0)
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

    int status;

    status = system("sudo insmod ../src/Kernal_Module/syscall.ko");

    if(WIFEXITED(status)&&(0 == WEXITSTATUS(status)))
    {
        printf("System call module has been loaded\n");
    }
    else
    {
        printf("Failed to load system call module\n");
        exit(-1);
    }

    unsigned long num_Process = 0;

    num_Process = syscall_get_Process_Info();

    print_Process_List(num_Process);

    status = system("sudo rmmod ../src/Kernal_Module/syscall.ko");
    
    if(WIFEXITED(status)&&(0 == WEXITSTATUS(status)))
    {
        printf("System call module has been unloaded\n");
    }
    else
    {
        printf("Failed to unload system call module.\n");
        exit(-1);
    }


    printf("Winner Winner, Chicken Chicken.\n");

    exit(0);
}