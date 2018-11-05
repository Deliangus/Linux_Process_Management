#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_HASH_TABLE 100
#define PATH_TO_KNOWN_PROCESS "../classification/known_Process"
#define PATH_TO_UNKNOWN_PROCESS "../classification/unknown_Process"
#define PATH_TO_SUCCESS_PROCESS "../classification/known_Process"
#define PATH_TO_FAILURE_PROCESS "../classification/known_Process"
struct process_Node
{
    char * Name;
    int pid;
    int status;
    struct process_Node * previous;
    struct process_Node * next;
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

int load_unknown_Process();
int load_known_Process();
int load_success_Process();
int load_failure_Process();

int load();