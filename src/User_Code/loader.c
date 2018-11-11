#include "loader.h"
#include "log.h"

int load()
{
    int count = 0;

    //Initialize process tables
    load_Table = (struct process_Table*)malloc(sizeof(struct process_Table));
    memset(load_Table->known_Process,NULL,SIZE_OF_HASH_TABLE);
    memset(load_Table->unknown_Process,NULL,SIZE_OF_HASH_TABLE);
    memset(load_Table->success_Process,NULL,SIZE_OF_HASH_TABLE);
    memset(load_Table->failure_Process,NULL,SIZE_OF_HASH_TABLE);

    count += load_unknown_Process();
    count += load_known_Process();
    count += load_success_Process();
    count += load_failure_Process();

    //TO DO: output log
    
    return count;
}

int load_known_Process()
{
    FILE* fp = fopen(PATH_TO_KNOWN_PROCESS,"r");

    char buff[255];

    while(EOF!=fscanf(fp, "%s", buff))
    {
        if(strlen(buff)>0)
        {
            char name_Pro = strlwr(buff);

            int hash_value = hashing_Process(name_Pro);

            if(load_Table!=NULL)
            {
                if(load_Table->known_Process[hash_value]==NULL)
                {
                    struct process_Node pro;
                    pro.Name = name_Pro;
                    pro.pid = -1;
                    pro.status = -1;
                    pro.next = NULL;
                    pro.previous = &pro;

                    load_Table->known_Process[hash_value] = &pro;

                    //TO DO: log
                }
                else
                {
                    struct process_Node* headpt = load_Table->known_Process[hash_value];

                    struct process_Node pro;
                    pro.Name = name_Pro;
                    pro.pid = -1;
                    pro.status = -1;
                    pro.next = NULL;
                    pro.previous = headpt->previous;

                    headpt->previous->next = &pro;
                    headpt->previous = &pro;

                    //TO DO: log
                }
            }
            else
            {
                //TO DO: log
                exit(-1);
            }
        }
    }

    //TO DO: log
}