#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "log.h"

static FILE *gLogFp = NULL;


bool openFile()
{
    if((gLogFp = fopen("./log.txt", "a+")) == NULL) {
        printf(" log.txt file open failed...\n");
        return false;
    }
    return true;
}
void closeFile()
{
    fclose(gLogFp);
}

void logMessage(LOG_TYPE type, const char *fmt, ... )
{
    va_list args;
    time_t t_now;
    struct tm *tm_ptr;

    t_now = time(NULL);
    tm_ptr = localtime( &t_now );

    fprintf(gLogFp, "%s  %04d-%02d-%02d  %02d:%02d:%02d ", 
            (type == DEBUG ? "DBG" : type == WARN ? "WAR" : type == INFO ? "RUN" : type == ERROR ? "ERR" : "---"),
            tm_ptr->tm_year + 1900,
            tm_ptr->tm_mon + 1,
            tm_ptr->tm_mday,
            tm_ptr->tm_hour,
            tm_ptr->tm_min,
            tm_ptr->tm_sec
            );
    va_start( args, fmt );
    vfprintf( gLogFp, fmt, args );
    va_end( args );

    fflush(gLogFp);

    return ;

}
int main()
{
    if(!openFile())
        return -1; 
    DBG_LOG("---DBG---  = %s", "I'm Debug"); 
    ERR_LOG("---ERR---  = %s", "I'm Error"); 
    INFO_LOG("---INF---  = %s", "I'm Info"); 
    WARN_LOG("---WAR---  = %s", "I'm Warn"); 
    return 0;
}
