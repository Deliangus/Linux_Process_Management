#include "policy.h"
#include "loader.h"

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

//Kill all prcess in process_Kill List
int apply_Process_Kill()
{
    //TO DO
}

//Eliminate all prcess in process_Eliminate List
int apply_Process_Eliminate()
{
    //TO DO
}