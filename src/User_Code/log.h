/*
log.h

Created by Yuxiang Luo on long long time ago.

Copyright @ 2018 Yuxiang Luo, Jonathan Karkour, Matt. All right reserved.
*/

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