#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "loader.h"

FILE* log_Output = NULL;


void log_Output_Initialize();

void log_Print_To_Terminal(char *string);

void log_Print(char *string);