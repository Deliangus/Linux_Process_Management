#include "monitor.h"


static unsigned long syscall_get_Process_Info(void)
{
    printf("..........Getting list of processes\n");

    memset(&process_List,0,sizeof(struct process)*512);

    printf("List Length before:%u\n",process_List[0].pid);

    unsigned long process_count = syscall(HIJACKED_SYSCALL,process_List);
    if(process_count!=0)
    {
        printf("..........Failed to get list of prcesses\t%lu\n",process_count);
    }
    else
    {
        printf("..........Successed to get list of prcesses\t%lu\n",process_count);
    }

    return process_count;
}

static void print_Process_List(pid_t length)
{
    printf("List Length:%u\n",length);

    for(int i = 0;i<length;i++)
    {
        printf("\t%u",process_List[i].pid);
        printf("\t%s\n",process_List[i].name);
    }
    
    return;
}

static int kill_Process(pid_t pid,char * name)
{

    char instruction [50] = "kill ";

    sprintf(instruction, "%s %d","kill", pid);

    int shell = system(instruction);

    if(shell==0)
    {
        printf("Process\t%u\t%s has been killed\n",pid,name);

    }
    else
    {
        printf("Failed: kill process\t%u\t%s\n.",pid,name);
    }
}

static void kernel_Module_Load()
{
    //Veriable used to receive shell command result
    // 0 when shell command executed correctly
    int status;

    status = system("sudo insmod src/Kernal_Module/syscall.ko");

    if(WIFEXITED(status)&&(0 == WEXITSTATUS(status)))
    {
        printf("System call module has been loaded\n");
    }
    else
    {
        printf("Failed to load system call module\n");
        exit(-1);
    }

    return status;
}

int main(int args, char **argv)
{
    
    //Get the path of program folder
    //../Linux_Process_Managing_Module
    getcwd(path_Root,sizeof(path_Root));

    kernel_Module_Load();

    if(syscall_Get_Process_Info()==0)
    {
        process_List_Print(process_List[0].pid);

        printf("Winner Winner, Chicken Dinner.\n");

        exit(0);
    }
    else
    {
        printf("Failed to get process list.\n");
    }

    //Remove Kernal Module
    status = system("sudo rmmod src/Kernal_Module/syscall.ko");

    if(WIFEXITED(status)&&(0 == WEXITSTATUS(status)))
    {
        printf("System call module has been unloaded\n");
    }
    else
    {
        printf("Failed to unload system call module.\n");
        exit(-1);
    }
}