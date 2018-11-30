#include "monitor.h"
#include "loader.h"
#include "log.h"
#include "policy.h"

void initialize_variables()
{
    sem_init(&sem_mutex_log,0,1);
    log_Print_To_Terminal("Initializing variables.\n");
    //Get the path of program folder
    //../Linux_Process_Management
    getcwd(PATH_ROOT,sizeof(PATH_ROOT));

    sprintf(PATH_KRN,"%s%s%s","src/Kernel_Module/",Kernel_Name_String,".ko");
    sprintf(PATH_TO_PROCESS_WHITE_LIST,"%s/%s",PATH_ROOT,"classification/process_White_List");
    sprintf(PATH_TO_PROCESS_UNKNOWN,"%s/%s",PATH_ROOT,"classification/process_Unknown");
    sprintf(PATH_TO_PROCESS_KILL,"%s/%s",PATH_ROOT,"classification/process_Kill");
    sprintf(PATH_TO_PROCESS_ELIMINATE,"%s/%s",PATH_ROOT,"classification/process_Eliminate");
    sprintf(PATH_TO_PROCESS_DEFINED,"%s/%s",PATH_ROOT,"classification/process_Defined");
    sprintf(PATH_TO_PROCESS_LIST,"%s/%s",PATH_ROOT,"classification/process_List");

    TYPE_MARK_POSITION = strlen(PATH_ROOT)+strlen("/classification/process_");

    operation  = 0;

    memset(&process_List,0,sizeof(struct process)*512);

    sem_init(&sem_mutex_Process_List,0,1);
    sem_init(&sem_mutex_Operation,0,1);
    sem_init(&sem_mutex_White_List,0,1);
    sem_init(&sem_mutex_Unknown,0,1);
    sem_init(&sem_mutex_Kill,0,1);
    sem_init(&sem_mutex_Eliminate,0,1);
    sem_init(&sem_mutex_Define,0,1);

    log_Print_To_Terminal("Initialized variables.\n\n");
}

static void* syscall_Get_Process_Info()
{
    log_Print_To_File("Getting list of processes\n");

    sem_wait(&sem_mutex_Process_List);
    unsigned long process_count = syscall(HIJACKED_SYSCALL,process_List);
    sem_post(&sem_mutex_Process_List);

    if(process_count!=0)
    {
        log_Print_To_File("Failed to get list of prcesses.\n\n");
    }
    else
    {
        log_Print_To_File("Successed to get list of prcesses\n\n");
    }
}

static void print_Process_List(pid_t length)
{
    printf("List Length:%u\n",length);

    sem_wait(&sem_mutex_Process_List);
    for(int i = 0;i<length;i++)
    {
        printf("\t%u",process_List[i].pid);
        printf("\t%s\n",process_List[i].name);
    }
    sem_post(&sem_mutex_Process_List);

    return;
}

static void kernel_Module_Load()
{
    log_Print_To_File("Loading Kernel Module\n");
    //Veriable used to receive shell command result
    // 0 when shell command executed correctly
    int status;

    char command[200];
    sprintf(command,"%s%s","sudo insmod ",PATH_KRN);

    status = system(command);

    if(WIFEXITED(status)&&(0 == WEXITSTATUS(status)))
    {
        log_Print_To_File("System call module has been loaded\n\n");
    }
    else
    {
        log_Print_To_File("Failed to load system call module\n\n");
    }
}

static void kernel_Module_Remove()
{
    log_Print_To_File("Removing Kernel Module\n");
    //Veriable used to receive shell command result
    // 0 when shell command executed correctly
    int status;

    char command[200];
    sprintf(command,"%s%s","sudo rmmod ",PATH_KRN);

    //Remove Kernal Module
    status = system(command);

    if(WIFEXITED(status)&&(0 == WEXITSTATUS(status)))
    {
        log_Print_To_File("System call module has been unloaded\n\n");
    }
    else
    {
        log_Print_To_File("Failed to unload system call module.\n\n");
    }

}

void* background()
{
    while(1)
    {
        syscall_Get_Process_Info();

        sem_wait(&sem_mutex_Process_List);
        sem_wait(&sem_mutex_Kill);
        sem_wait(&sem_mutex_Unknown);
        sem_wait(&sem_mutex_White_List);
        sem_wait(&sem_mutex_Eliminate);
        int result = table_Update_Pid(process_List[0].pid);
        sem_post(&sem_mutex_Eliminate);
        sem_post(&sem_mutex_White_List);
        sem_post(&sem_mutex_Unknown);
        sem_post(&sem_mutex_Kill);
        sem_post(&sem_mutex_Process_List);
        
        if(result)
        {
            process_List_Print_To_File(process_List[0].pid,path_To_Process_List);

            if(result & 0b0001)
            {
                sem_wait(&sem_mutex_Unknown);
                print_List(process_Unknown,PATH_TO_PROCESS_UNKNOWN);
                sem_post(&sem_mutex_Unknown);
            }

            if(result & 0b0010)
            {
                sem_wait(&sem_mutex_Kill);
                apply_Process_Kill();
                sem_post(&sem_mutex_Kill);
            }

            if(result & 0b0100)
            {
                sem_wait(&sem_mutex_Eliminate);
                apply_Process_Eliminate();
                sem_post(&sem_mutex_Eliminate);
            }

            if(result & 0b1000)
            {
                sem_wait(&sem_mutex_White_List);
                print_List(process_White_List,PATH_TO_PROCESS_WHITE_LIST);
                sem_post(&sem_mutex_White_List);
            }
        }

        sem_wait(&sem_mutex_Operation);
        if(operation==-1)
        {
            sem_post(&sem_mutex_Operation);
            break;
        }
        sem_post(&sem_mutex_Operation);

        sleep(2);
    }
}

static void process_List_Print_To_File(pid_t length,char* file_path)
{
    log_Print_To_File("Printing process list to file.\n");

    FILE* outputFile = fopen(file_path,"w");

    fprintf(outputFile,"List Length:%u\n",length);

    sem_wait(&sem_mutex_Process_List);
    for(int i = 0;i<length;i++)
    {
        fprintf(outputFile,"%s\n",process_List[i].name);
    }
    sem_post(&sem_mutex_Process_List);

    fclose(outputFile);

    log_Print_To_File("Process list printed to file.\n\n");
    
    return;
}

void* user_Command()
{
    while(operation != -1)
    {
        char instruction[20];
        log_Print("Instruction:");
        scanf("%s",instruction);

        if(instruction[0]=='q')
        {
            sem_wait(&sem_mutex_Operation);
            operation = -1;
            sem_post(&sem_mutex_Operation);
        }

        switch(instruction[0])
        {
            case('q'):
            {
                sem_wait(&sem_mutex_Operation);
                operation = -1;
                sem_post(&sem_mutex_Operation);
                break;
            }
            case('p'):
            {
                scanf("%s",instruction);

                switch(instruction[0])
                {
                    case('w'):
                    {
                        sem_wait(&sem_mutex_White_List);
                        print_List_Terminal(process_White_List,PATH_TO_PROCESS_WHITE_LIST);
                        sem_post(&sem_mutex_White_List);
                        break;
                    }
                    case('u'):
                    {
                        sem_wait(&sem_mutex_Unknown);
                        print_List_Terminal(process_Unknown,PATH_TO_PROCESS_UNKNOWN);
                        sem_post(&sem_mutex_Unknown);
                        break;
                    }
                    case('k'):
                    {
                        sem_wait(&sem_mutex_Kill);
                        print_List_Terminal(process_Kill,PATH_TO_PROCESS_KILL);
                        sem_post(&sem_mutex_Kill);
                        break;
                    }
                    case('e'):
                    {
                        sem_wait(&sem_mutex_Eliminate);
                           print_List_Terminal(process_Eliminate,PATH_TO_PROCESS_ELIMINATE);
                        sem_post(&sem_mutex_Eliminate);
                        break;
                    }
                    case('d'):
                    {
                        sem_wait(&sem_mutex_Unknown);
                        print_List_Terminal(process_Unknown,PATH_TO_PROCESS_DEFINED);
                        sem_post(&sem_mutex_Unknown);
                        break;
                    }
                    case('p'):
                    {
                        sem_wait(&sem_mutex_Process_List);
                        print_Process_List(process_List[0].pid);
                        sem_post(&sem_mutex_Process_List);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case('k'):
            {
                scanf("%s",instruction);
                execute_Kill(get_Process_Pid(instruction));
            }
            default:
            {
                printf("Instruction error.\n");
                break;
            }
        }
    }

}

int main(int args, char **argv)
{
    initialize_variables();

    log_Output_Initialize(path_Root);

    load();

    apply_Process_Defined();

    kernel_Module_Load();


    pthread_t pth_background;
    //pthread_t pth_user;

    pthread_create(&pth_background,NULL,&background,NULL);

    user_Command();

    pthread_join(pth_background,NULL);

    kernel_Module_Remove();

    finalizing_classification();

    return 0;
}