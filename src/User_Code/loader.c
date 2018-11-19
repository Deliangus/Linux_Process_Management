#include "loader.h"

void load()
{
    int count = 0;

    //Initialize process tables
    memset(process_White_List,0,SIZE_OF_HASH_TABLE);
    memset(process_Unknown,0,SIZE_OF_HASH_TABLE);
    memset(process_Kill,0,SIZE_OF_HASH_TABLE);
    memset(process_Eliminate,0,SIZE_OF_HASH_TABLE);

    load_List(PATH_TO_PROCESS_WHITE_LIST,process_White_List);
    log_print("White list is loaded\n");

    load_List(PATH_TO_PROCESS_UNKNOWN,process_Unknown);
    log_print("Unknown list is loaded\n");

    load_list(PATH_TO_PROCESS_KILL,process_Kill);
    log_print("Kill list is loaded\n");

    load_list(PATH_TO_PROCESS_ELIMINATE,process_Eliminate);
    log_print("Eliminate list is loaded\n");
    
    return count;
}

//Return a hash value according to given process name
int hashing_Process(char*Name)
{
    //TO DO
}

int load_List(char*path,struct process_Node* destination[SIZE_OF_HASH_TABLE])
{
    FILE* fp = fopen(path,"r");

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
                    struct process_Node pro;

                    strcpy(pro.name,buff);
                    pro.pid = -1;
                    pro.status = -1;
                    pro.next = NULL;
                    pro.previous = &pro;

                    destination[hash_value] = &pro;
                }
                else
                {
                    struct process_Node* headpt = destination[hash_value];

                    struct process_Node pro;

                    strcpy(pro.name,buff);

                    pro.pid = -1;
                    pro.status = -1;
                    pro.previous = headpt->previous;

                    headpt->previous->next = &pro;
                    headpt->previous = &pro;
                }
            }
            else
            {
                log_print("Failed to load list [Name of 0 length readed]");
                exit(-1);
            }
        }
    }

}

//Get pid of process according to its name from the four process_Node* List
pid_t get_Process_Pid(char* name)
{
    //TO Do
}

//Get action to do with process given its name
union process_Type get_Process_Type(char *name)
{
    //TO DO
}