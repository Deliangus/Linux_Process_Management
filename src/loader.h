#include <stdio.h>

#define SIZE_OF_HASH_TABLE 100
struct process_Node
{
    char * Name;
    int pid;
    bool status;

};

struct process_Table
{
    struct process_Node* known_Process [SIZE_OF_HASH_TABLE];
    struct process_Node* unknown_Process [SIZE_OF_HASH_TABLE];
    struct process_Node* success_Process [SIZE_OF_HASH_TABLE];
    struct process_Node* failure_Process [SIZE_OF_HASH_TABLE];
};

struct process_Table* load_Table;

int hashing_Process(char*Name);

bool load_unknown_Process();
bool load_known_Process();
bool load_success_Process();
bool load_failure_Process();

bool load();