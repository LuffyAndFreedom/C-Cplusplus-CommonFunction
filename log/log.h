#ifndef _LOG_H_
#define _LOG_H_
#include <string>
#include <string.h>

using namespace std;

typedef enum outputLogType
{
    //enum 如果不赋初值,默认从0开始
    DEBUG = 1,
    INFO,
    WARN,
    ERROR,
} LOG_TYPE;

#ifndef LOG_MODE
#define LOG_MODE "LOG "
#endif

void logMessage( LOG_TYPE type, const char *fmt, ... );

//##args的意思，就是把args...中的多个参数，串连起来。
#define DBG_LOG( fmt, args... ) \
    logMessage( DEBUG, LOG_MODE" %s:%d:%s " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args );

#define INFO_LOG( fmt, args... ) \
    logMessage( INFO, LOG_MODE" %s:%d:%s " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args );

#define WARN_LOG( fmt, args... ) \
    logMessage( WARN, LOG_MODE" %s:%d:%s " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args );

#define ERR_LOG( fmt, args... ) \
    logMessage( ERROR, LOG_MODE" %s:%d:%s " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args );

#endif
