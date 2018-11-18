#include "log.h"

int log_Output_Initialize()
{
    char log_Path[200];

    time_t rawtime;
    
    time(&rawtime);

    struct tm *timeinfo = localtime(&rawtime);

    sprintf(log_Path,"%s %s_%d_%d_%d_%d_%s",path_Root,"\\log\\log",timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);

    log_Output = fopen(log_Path,"-w");

    //TO DO
}