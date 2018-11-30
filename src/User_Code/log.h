#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

char log_Path[200];
sem_t sem_mutex_log;

void log_Output_Initialize(char *);

void log_Print_To_Terminal(char *);

void log_Print(char *);

void log_Print_To_File(char*);