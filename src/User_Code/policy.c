#include "policy.h"
#include "loader.h"
#include "log.h"

void kill_Process(char * name)
{

    pid_t pid = get_Process_Pid(name);
    
    execute_Kill(pid);
}

void eliminate_Process(char * name)
{

    pid_t pid = get_Process_Pid(name);
    
    execute_Eliminate(pid);
}

//Kill all prcess in process_Kill List
int apply_Process_Kill()
{
    int i = 0;

    int count = 0;

    for(i = 0;i<SIZE_OF_HASH_TABLE;i++)
    {
        if(process_Kill[i]!=NULL)
        {
            struct process_Node* temp = process_Kill[i];
            
            if(temp->pid>0)
            {
                execute_Kill(temp->pid);

                count++;
            }

            temp = temp->next;

            while(temp!=process_Kill[i])
            {
                if(temp->pid>0)
                {
                    execute_Kill(temp->pid);

                    count++;
                }

                temp = temp->next;
            }
        }
    }

    return count;
}

//Eliminate all prcess in process_Eliminate List
int apply_Process_Eliminate()
{
    int i = 0;

    int count = 0;

    for(i = 0;i<SIZE_OF_HASH_TABLE;i++)
    {
        if(process_Kill[i]!=NULL)
        {
            struct process_Node* temp = process_Kill[i];
            
            if(temp->pid>0)
            {
                execute_Eliminate(temp->pid);
                count++;
            }

            temp = temp->next;

            while(temp!=process_Kill[i]&&temp!=NULL)
            {
                if(temp->pid>0)
                {
                    execute_Eliminate(temp->pid);
                    count++;
                }

                temp = temp->next;
            }
        }
    }

    return count;
}

void execute_Kill(pid_t pid)
{
    char instruction [50];

    sprintf(instruction, "sudo kill %d", pid);

    int shell = system(instruction);

    if(shell==0)
    {
        //log_Print_To_File("Process\t%u\t%s has been killed\n",pid);

    }
    else
    {
        //log_Print_To_File("Failed: kill process\t%u\t%s\n.",pid);
    }
}

void execute_Eliminate(pid_t pid)
{
    //TO DO
    printf("Execute Eliminate has not been implemented\n");
}