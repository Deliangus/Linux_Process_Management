#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* log_Output;

void log_Output_Initialize(char *);

void log_Print_To_Terminal(char *string);

void log_Print(char *string);