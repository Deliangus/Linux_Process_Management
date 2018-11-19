#include "log.h"

void log_Output_Initialize()
{
    char log_Path[200];

    time_t rawtime;
    
    time(&rawtime);

    struct tm *timeinfo = localtime(&rawtime);

    sprintf(log_Path,"%s %s_%d_%d_%d_%d_%s",path_Root,"\\log\\log",timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);

    log_Output = fopen(log_Path,"-w");

    if(log_Output==NULL)
    {
        log_Print_To_Terminal("Failed to open log file\n");
        exit(-4);
    }
    else
    {
        log_Print("Log initialized.\n");
        
    }
}

void log_Print_To_Terminal(char*string)
{
    printf("%s\n",string);
}

void log_Print(char *string)
{
    printf("%s\n",string);
    fprintf(log_Output,"%s\n",string);
}