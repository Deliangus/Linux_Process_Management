#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <ctype.h>
#include <linux/limits.h>


#define PATH_TO_PROCESS_WHITE_LIST path_Table_White_List
#define PATH_TO_PROCESS_UNKNOWN path_Table_Unknown
#define PATH_TO_PROCESS_KILL path_Table_Kill
#define PATH_TO_PROCESS_ELIMINATE path_Table_Eliminate

#define SIZE_OF_HASH_TABLE 512

#define LENGTH_PROCESS_NAME 50

char path_Table_White_List[200];
char path_Table_Unknown[200];
char path_Table_Kill[200];
char path_Table_Eliminate[200];

struct process_Node
{
    char name[LENGTH_PROCESS_NAME];
    pid_t pid;
    int status;
    struct process_Node * previous;
    struct process_Node * next;
};

union process_Type
{
    int White;
    int Unknown;
    int Kill;
    int Eliminate;
};

struct process_Node* process_Unknown [SIZE_OF_HASH_TABLE];
struct process_Node* process_White_List [SIZE_OF_HASH_TABLE];
struct process_Node* process_Kill [SIZE_OF_HASH_TABLE];
struct process_Node* process_Eliminate [SIZE_OF_HASH_TABLE];

int hashing_Process(char*Name);

int load_List(char*,struct process_Node*[]);

void load();

struct process_Node* get_Process(char *name);

pid_t get_Process_Pid(char *name);

union process_Type get_Process_Type(char *name);

void table_Update_Pid(pid_t);

void print_List(struct process_Node**);

void print_Four_List();