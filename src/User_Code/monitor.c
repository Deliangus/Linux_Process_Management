#include "monitor.h"
#include "loader.h"
#include "log.h"

static void syscall_get_Process_Info(void)
{
    log_Print("Getting list of processes\n");

    memset(&process_List,0,sizeof(struct process)*512);


    unsigned long process_count = syscall(HIJACKED_SYSCALL,process_List);

    if(process_count!=0)
    {
        log_Print("Failed to get list of prcesses.\n");
        exit(-2);
    }
    else
    {
        log_Print("Successed to get list of prcesses\n");

    }
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

static void kernel_Module_Load()
{
    log_Print("Loading Kernel Module\n");
    //Veriable used to receive shell command result
    // 0 when shell command executed correctly
    int status;

    char command[200];
    sprintf(command,"%s%s","sudo insmod ",PATH_KRN);

    status = system(command);

    if(WIFEXITED(status)&&(0 == WEXITSTATUS(status)))
    {
        log_Print("System call module has been loaded\n");
    }
    else
    {
        log_Print("Failed to load system call module\n");
        exit(-1);
    }
}

static void kernel_Module_Remove()
{
    log_Print("Removing Kernel Module\n");
    //Veriable used to receive shell command result
    // 0 when shell command executed correctly
    int status;

    char command[200];
    sprintf(command,"%s%s","sudo rmmod ",PATH_KRN);

    //Remove Kernal Module
    status = system(command);

    if(WIFEXITED(status)&&(0 == WEXITSTATUS(status)))
    {
        log_Print("System call module has been unloaded\n");
    }
    else
    {
        log_Print("Failed to unload system call module.\n");
        exit(-3);
    }

}

static void process_List_Print_To_File(pid_t length,char* file_path)
{
    log_Print("Printing process list to file.\n");

    FILE* outputFile = fopen(file_path,"w");

    fprintf(outputFile,"List Length:%u\n",length);

    for(int i = 0;i<length;i++)
    {
        fprintf(outputFile,"%s\n",process_List[i].name);
    }

    fclose(outputFile);

    log_Print("Process list printed to file.\n");
    
    return;
}

void initialize_variables()
{
    //Get the path of program folder
    //../Linux_Process_Management
    getcwd(PATH_ROOT,sizeof(PATH_ROOT));

    sprintf(PATH_KRN,"%s%s%s","src/Kernel_Module/",Kernel_Name_String,".ko");
}

int main(int args, char **argv)
{
    initialize_variables();

    log_Output_Initialize(path_Root);

    //load();

    kernel_Module_Load();

    syscall_get_Process_Info();

    kernel_Module_Remove();

    table_Update_Pid(process_List[0].pid);

    char ppp[200];

    sprintf(ppp,"%s/%s",path_Root,"log/process_List");

    process_List_Print_To_File(process_List[0].pid,ppp);

    return 0;
}