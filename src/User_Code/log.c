#include "log.h"

void log_Output_Initialize(char*path_Root)
{
    log_Print_To_Terminal("Initializing log.\n");

    FILE* log_Output;

    log_Output = NULL;

    time_t rawtime;
    
    time(&rawtime);

    struct tm *timeinfo = localtime(&rawtime);

    sprintf(log_Path,"%s/%s_%d_%d_%02d:%02d:%02d",path_Root,"log/log",timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);

    log_Output = fopen(log_Path,"w");

    if(log_Output==NULL)
    {
        log_Print_To_Terminal("Failed to open log file\n");
    }
    else
    {
        log_Print("Log initialized.\n");
        
    }

    fclose(log_Output);
}

void log_Print_To_Terminal(char*string)
{
    sem_wait(&sem_mutex_log);
    printf("%s",string);
    sem_post(&sem_mutex_log);
}

void log_Print_To_File(char*string)
{
    sem_wait(&sem_mutex_log);

    FILE *fp = fopen(log_Path,"a");

    fprintf(fp,"%s",string);

    fclose(fp);

    sem_post(&sem_mutex_log);
}

void log_Print(char*string)
{
    sem_wait(&sem_mutex_log);

    FILE *fp = fopen(log_Path,"a");

    fprintf(fp,"%s",string);
    printf("%s",string);

    fclose(fp);

    sem_post(&sem_mutex_log);
}