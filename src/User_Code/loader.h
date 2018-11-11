#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_type.h"


struct process_Table* load_Table;

int hashing_Process(char*Name);

int load_unknown_Process();
int load_known_Process();
int load_success_Process();
int load_failure_Process();

int load();