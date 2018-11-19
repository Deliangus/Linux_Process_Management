#include "policy.h"

int kill_Process(char * name)
{

    pid_t pid = get_Process_Pid(name);
    
    char instruction [50];

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