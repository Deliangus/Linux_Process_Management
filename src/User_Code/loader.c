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

    apply_Process_Defined();
    log_Print("Process defined has been applied.\n");

    log_Print("Process policies loaded.\n");
}

//Return a hash value according to given process name
int hashing_Process(char*Name)
{
    //TO DO

    //Default solution:

    int i = 0;
    int result = 1;
    for(i = 0;i<strlen(Name);i++)
    {
        result *= (int)Name[i];
        result ++;
        result%=SIZE_OF_HASH_TABLE;
    }
    return result;
}

int load_List(char*path,struct process_Node* destination[SIZE_OF_HASH_TABLE])
{
    FILE* fp = fopen(path,"r");

    if(fp!=NULL&&destination!=NULL)
    {
        char buff[LENGTH_PROCESS_NAME];
    
        while(EOF!=fscanf(fp, "%s", buff))
        {
            if(strlen(buff)>0)
            {
                struct process_Node* temp = (struct process_Node*)malloc(sizeof(struct process_Node));

                temp->next = NULL;
                temp->pid = -1;
                temp->type = path[TYPE_MARK_POSITION];

                strcpy(temp->name,buff);

                insert_To_Table(temp,destination);
            }
            else
            {
                log_Print("Failed to load list\n");
            }
        }
    }
    else
    {
        log_Print("Faild to load list, file open failure\n");
        log_Print(path);
    }
}

//Get process_Node from the four hash tables
struct process_Node* get_Process(char *name)
{
    log_Print("Getting process:\t");
    log_Print(name);
    log_Print("\n");

    int hash_value = hashing_Process(name);

    log_Print(name);
    printf("\t%d\n",hash_value);
    
    struct process_Node* result;

    result = NULL;

    if(process_White_List[hash_value]!=NULL)
    {
        struct process_Node* temp = process_White_List[hash_value];
        struct process_Node* headpt = process_White_List[hash_value];

        if(strcmp(name,temp->name)==0)
        {
            result = temp;
        }
        else
        {
            temp = temp->next;
        }

        while(temp!=headpt)
        {
            if(strcmp(name,temp->name)==0)
            {
                result = temp;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }

        if(result == NULL)
            log_Print("No found in White list.\n");
        else
            log_Print("Got process in White list.\n");
    }

    if(process_Unknown[hash_value]!=NULL)
    {
        struct process_Node* temp = process_Unknown[hash_value];
        struct process_Node* headpt = process_Unknown[hash_value];

        if(strcmp(name,temp->name)==0)
        {
            result = temp;
        }
        else
        {
            temp = temp->next;
        }

        while(temp!=headpt)
        {
            if(strcmp(name,temp->name)==0)
            {
                result = temp;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }

        if(result == NULL)
            log_Print("No found in Unknown.\n");
        else
            log_Print("Got process in Unknown.\n");
    }

    if(process_Kill[hash_value]!=NULL)
    {
        struct process_Node* temp = process_Kill[hash_value];
        struct process_Node* headpt = process_Kill[hash_value];

        if(strcmp(name,temp->name)==0)
        {
            result = temp;
        }
        else
        {
            temp = temp->next;
        }

        while(temp!=headpt)
        {
            if(strcmp(name,temp->name)==0)
            {
                result = temp;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }

        if(result == NULL)
            log_Print("No found in Kill.\n");
        else
            log_Print("Got process in Kill.\n");
    }

    if(process_Eliminate[hash_value]!=NULL)
    {
        struct process_Node* temp = process_Eliminate[hash_value];
        struct process_Node* headpt = process_Eliminate[hash_value];

        if(strcmp(name,temp->name)==0)
        {
            result = temp;
        }
        else
        {
            temp = temp->next;
        }

        while(temp!=headpt)
        {
            if(strcmp(name,temp->name)==0)
            {
                result = temp;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }

        if(result == NULL)
            log_Print("No found in Eliminate.\n");
        else
            log_Print("Got process in Eliminate.\n");
    }

    return result;
}

//Get pid of process according to its name from the four process_Node* List
pid_t get_Process_Pid(char* name)
{
    struct process_Node* temp = get_Process(name);

    pid_t pid = 0;
    if(temp!=NULL)
    {
        pid = get_Process(name)->pid;
    }
    else
    {
        pid = -1;
    }

    return pid;
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

    for(int i = 1;i<length;i++)
    {
        temp = get_Process(process_List[i].name);

        if(temp!=NULL)
        {
            temp->pid = process_List[i].pid;
        }
        else
        {
            temp = (struct process_Node*)malloc(sizeof(struct process_Node));

            strcpy(temp->name,process_List[i].name);
            temp->pid = process_List[i].pid;
            temp->type = type_UKNOWN;

            insert_To_Table(temp,process_Unknown);
        }
    }

    log_Print("Pid Updated\n");
}

void print_List(struct process_Node**table,char*path)
{
    FILE *fp = fopen(path,"w");

    log_Print("Printing table.\n");

    int i = 0;

    for(i = 0;i<SIZE_OF_HASH_TABLE;i++)
    {
        if(table[i]!=NULL)
        {
            struct process_Node* temp = table[i];
            struct process_Node* headpt = table[i];

            do
            {
                if(strlen(temp->name)>0)
                {
                    fprintf(fp,"%s\n",temp->name);
                }

                temp = temp->next;
            }
            while(temp!=headpt);
        }
    }

    log_Print("Table printed\n");

    fclose(fp);
}

void print_Four_List()
{
    log_Print("Printing white list and pid.\n");

    print_List(process_White_List,PATH_TO_PROCESS_WHITE_LIST);

    log_Print("Printing kill list and pid.\n");

    print_List(process_Kill,PATH_TO_PROCESS_KILL);

    log_Print("Printing unknown list and pid.\n");

    print_List(process_Unknown,PATH_TO_PROCESS_UNKNOWN);

    log_Print("Printing eliminate list and pid.\n");

    print_List(process_Eliminate,PATH_TO_PROCESS_ELIMINATE);

    print_List(process_Unknown,PATH_TO_PROCESS_DEFINED);
}

void apply_Process_Defined()
{
    log_Print("Applying process defined.\n");

    FILE* fp = fopen(PATH_TO_PROCESS_DEFINED,"r");

    if(fp!=NULL)
    {
        char buff[LENGTH_PROCESS_NAME];
        char define_Type;
    
        while(EOF!=fscanf(fp, "%s %c", buff,&define_Type))
        {
            log_Print(buff);
            log_Print("----");
            putchar(define_Type);
            putchar('\n');
            if(strlen(buff)>0)
            {
                if(define_Type != type_UKNOWN)
                {
                    struct process_Node* temp = remove_From_Unknown(buff);
                    temp->type = define_Type;

                    if (define_Type == type_WHITE)
                        insert_To_Table(temp,process_White_List);
                    else if(define_Type == type_KILL)
                        insert_To_Table(temp,process_Kill);
                    else if(define_Type == type_ELIMINATE)
                        insert_To_Table(temp,process_Eliminate);
                    else
                        log_Print("Input error in process_Defined\n");
                }
            }
        }
    }
    else
    {
        log_Print("Faild to apply process defined, file open failure\n");
        log_Print(PATH_TO_PROCESS_DEFINED);
    }

    log_Print("Applied process defined.\n");
}

void remove_From_Tables(char* name)
{
    //TO DO
}

struct process_Node* remove_From_Unknown(char* name)
{
    int hash_value = hashing_Process(name);

    struct process_Node* result = NULL;

    if(process_Unknown[hash_value]==NULL)
    {
        log_Print("Remove from unknown failure.\n");
    }
    else
    {
        struct process_Node*temp = process_Unknown[hash_value];
        struct process_Node*headpt = process_Unknown[hash_value];

        if(strcmp(temp->name,name)==0)
        {
            temp->next->previous = temp->previous;
            process_Unknown[hash_value] = temp->next;

            result = temp;
        }
        else
        {
            temp = temp->next;

            while(temp!=headpt&&(strcmp(temp->name,name)!=0))
            {
                temp= temp->next;
            }

            if(temp == headpt || strcmp(temp->name,name)!=0)
            {
                log_Print("Remove from unknown failure.\n");
                result =  NULL;
            }
            else
            {
                temp->next->previous = temp->previous;
                temp->previous->next = temp->next;

                result = temp;
            }
        }
    }

    return result;
}


void insert_To_Table(struct process_Node*pro,struct process_Node* destination[SIZE_OF_HASH_TABLE])
{
    int hash_value = hashing_Process(pro->name);

    if(destination[hash_value]==NULL)
    {
        pro->hash_Value = hash_value;
        pro->next = pro;
        pro->previous = pro;
        destination[hash_value] = pro;
    }
    else
    {
        struct process_Node* headpt = destination[hash_value];

        pro->hash_Value = hash_value;

        pro->previous = headpt->previous;
        pro->next = headpt;

        headpt->previous->next = pro;
        headpt->previous = pro;
    }
}

void finalizing_classification()
{
    print_Four_List();
}