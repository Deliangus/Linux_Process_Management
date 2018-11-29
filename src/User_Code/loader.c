#include "loader.h"
#include "log.h"
#include "monitor.h"

void load()
{

    int count = 0;

    log_Print("Loading process policies.\n");

    //Initialize process tables
    memset(process_White_List,0,SIZE_OF_HASH_TABLE);
    memset(process_Unknown,0,SIZE_OF_HASH_TABLE);
    memset(process_Kill,0,SIZE_OF_HASH_TABLE);
    memset(process_Eliminate,0,SIZE_OF_HASH_TABLE);

    log_Print("Tables intialized.\n");

    load_List(PATH_TO_PROCESS_WHITE_LIST,process_White_List);
    log_Print("White list is loaded\n");

    load_List(PATH_TO_PROCESS_UNKNOWN,process_Unknown);
    log_Print("Unknown list is loaded\n");

    load_List(PATH_TO_PROCESS_KILL,process_Kill);
    log_Print("Kill list is loaded\n");

    load_List(PATH_TO_PROCESS_ELIMINATE,process_Eliminate);
    log_Print("Eliminate list is loaded\n");

    log_Print("Process policies loaded.\n");
}

//Return a hash value according to given process name
int hashing_Process(char*Name)
{
    //TO DO

    //Default solution:

    int i = 0;
    int result = 0;
    for(i = 0;i<strlen(Name);i++)
    {
        result += (int)Name[i];
    }
    return result%SIZE_OF_HASH_TABLE;
}

int load_List(char*path,struct process_Node* destination[SIZE_OF_HASH_TABLE])
{
    FILE* fp = fopen(path,"r");

    if(fp!=NULL)
    {
        char buff[LENGTH_PROCESS_NAME];
    
        while(EOF!=fscanf(fp, "%s", buff))
        {
            if(strlen(buff)>0)
            {
                int hash_value = hashing_Process(buff);

                if(destination!=NULL)
                {
                    if(destination[hash_value]==NULL)
                    {
                        struct process_Node* pro = (struct process_Node*)malloc(sizeof(struct process_Node));

                        strcpy(pro->name,buff);
                        pro->pid = -1;
                        pro->status = -1;
                        pro->next = NULL;
                        pro->previous = pro;

                        destination[hash_value] = pro;
                    }
                    else
                    {
                        struct process_Node* headpt = destination[hash_value];

                        struct process_Node* pro = (struct process_Node*)malloc(sizeof(struct process_Node));

                        strcpy(pro->name,buff);

                        pro->pid = -1;
                        pro->status = -1;
                        pro->previous = headpt->previous;

                        headpt->previous->next = pro;
                        headpt->previous = pro;
                    }
                }
                else
                {
                    log_Print("Failed to load list\n");
                    exit(-1);
                }
            }
        }
    }
    else
    {
        log_Print("Faild to load list, file open failure\n");
        log_Print(path);
    }
}

//Get process_Node from the four hast tables
struct process_Node* get_Process(char *name)
{
    //TO DO
}

//Get pid of process according to its name from the four process_Node* List
pid_t get_Process_Pid(char* name)
{
    //TO DO
}

//Get action to do with process given its name
union process_Type get_Process_Type(char *name)
{
    //TO DO
}

void table_Update_Pid(pid_t length)
{
    log_Print("Updating pid to tables\n");

    struct process_Node* temp;

    for(int i = 1;i<=length;i++)
    {
        temp = get_Process(process_List[i].name);

        temp->pid = process_List[i].pid;
    }

    log_Print("Pid Updated\n");
}

void print_List(struct process_Node**table)
{
    log_Print("Printing table.\n");

    int i = 0;

    int count = 0;

    char info[100];

    for(i = 0;i<SIZE_OF_HASH_TABLE;i++)
    {
        if(table[i]!=NULL)
        {
            struct process_Node* temp = table[i];
            
            sprintf(info,"%s\t%d\n",temp->name,temp->pid);

            log_Print(info);

            count++;

            temp = temp->next;

            while(temp!=table[i]&&temp!=NULL)
            {
                count++;

                sprintf(info,"%s\t%d\n",temp->name,temp->pid);

                log_Print(info);

                temp = temp->next;
            }
        }
    }

    sprintf(info,"%s\t%d\n","Table printed.\t",count);

    log_Print(info);
}

void print_Four_List()
{
    log_Print("Printing white list and pid.\n");

    print_List(process_White_List);

    log_Print("Printing kill list and pid.\n");

    print_List(process_Kill);

    log_Print("Printing unknown list and pid.\n");

    print_List(process_Unknown);

    log_Print("Printing eliminate list and pid.\n");

    print_List(process_Eliminate);
}