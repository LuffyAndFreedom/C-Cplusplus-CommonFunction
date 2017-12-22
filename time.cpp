#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <cstring>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
#define BST (+1)
#define CCT (+8)

/*
 g++ -Wall -g time.cpp -o time
 */

void getTimeIntervalForSeconds()
{
    //difftime 函数使用获得时间差,精确到秒
    time_t t_start;
    time_t t_end;
    time(&t_start);
    sleep(5);
    time(&t_end);
    printf("间隔时间= %f.\n", difftime(t_end, t_start));
}

void getTimeIntervalForMicroseconds()
{
    // 计算两个时间的时间差, 精确到微秒
    struct timeval t_start;
    struct timeval t_end;
    gettimeofday(&t_start, NULL); //gettimeofday(&t_start,&tz);结果一样
    printf("t_start.tv_sec:%ld.\n", t_start.tv_sec);
    printf("t_start.tv_usec:%ld.\n",t_start.tv_usec);
    
    int temp = 500000000;
    while(temp--);

    gettimeofday(&t_end, NULL);  //gettimeofday(&t_end,&tz);结果一样
    printf("t_end.tv_sec:%ld.\n", t_end.tv_sec);
    printf("t_end.tv_usec:%ld.\n",t_end.tv_usec);
    
    float time_interval = (t_end.tv_sec - t_start.tv_sec) * 1000000 + (t_end.tv_usec - t_start.tv_usec);//微秒
    printf("time_interval is %.10f\n",time_interval);
}

void tm2formatTimeString()
{
    //strpftime 函数的使用,tm 格式时间转化为时间字符串
    time_t t_time;
    char buf[128];
    struct tm* tm_ptr = NULL;
    time(&t_time);
    tm_ptr = localtime(&t_time);
    //2017-12-21 18:53:58
    strftime(buf, 64, "%Y-%m-%d --- %H:%M:%S", tm_ptr);
    printf("formatTimeString = %s.\n", buf);
}

void timeString2tm()
{
    //strptime 函数的使用，字符串时间格式转化为 tm 结构体数据
    char buf[] = "2017-12-21 --- 18:54:46";
    struct tm tm_ptr;
    //2017-12-21 18:53:58
    strptime(buf, "%Y-%m-%d --- %H:%M:%S", &tm_ptr);
    printf("----strptime-----, the time is: \
            \n yday = %d \
            \n wday = %d \
            \n year = %d \
            \n mon =  %d \
            \n mday = %d \
            \n hour = %d \
            \n min =  %d \
            \n sec =  %d.\n", 
            tm_ptr.tm_yday,
            tm_ptr.tm_wday,
            tm_ptr.tm_year,
            tm_ptr.tm_mon,
            tm_ptr.tm_mday,
            tm_ptr.tm_hour, 
            tm_ptr.tm_min, 
            tm_ptr.tm_sec
          );
}

void getCurTime2Microseconds()
{
    //gettimeofday 函数的使用， 获取当前时间，精确到微秒
    struct timeval time_val;
    gettimeofday(&time_val, NULL); //gettimeofday(&start,&tz);结果一样
    printf("time_val.tv_sec:%ld.\n", time_val.tv_sec);
    printf("time_val.tv_usec:%ld.\n",time_val.tv_usec);
}

void getDiffTimezoneTime()
{
    //gmtime 函数的使用, 获取不同时区的时间
    time_t curtime;
    struct tm *tm_ptr;
    time(&curtime);
    
    /* 获取 GMT 时间 */
    tm_ptr = gmtime(&curtime );
                
    printf("当前的世界时钟：\n");
    printf("伦敦：%2d:%02d\n", (tm_ptr->tm_hour+BST)%24, tm_ptr->tm_min);
    printf("中国：%2d:%02d\n", (tm_ptr->tm_hour+CCT)%24, tm_ptr->tm_min);
}

void time_t__2__tm_switch()
{
    //gmtime 函数的使用， time_t 类型的UTC时间与 struct tm 格式之间的转换
    time_t t_time;
    struct tm *tm_ptr = NULL;
    time(&t_time);
    printf("time_t first time value = %ld.\n", t_time);

    tm_ptr = gmtime(&t_time);
    printf("time_t switch gmtime type, the time is: \
            \n yday = %d \
            \n wday = %d \
            \n year = %d \
            \n mon =  %d \
            \n mday = %d \
            \n hour = %d \
            \n min =  %d \
            \n sec =  %d \
            \n isdst =%d.\n", 
            tm_ptr->tm_yday,
            tm_ptr->tm_wday,
            tm_ptr->tm_year,
            tm_ptr->tm_mon,
            tm_ptr->tm_mday,
            tm_ptr->tm_hour, 
            tm_ptr->tm_min, 
            tm_ptr->tm_sec,
            tm_ptr->tm_isdst
            );
    
    t_time = mktime(tm_ptr); /*重新转换为time_t类型的UTC时间，这里有一个时区的转换, 时间为0区的时间, 所以一下使用的时间都为0区的时间*/   
    printf("gmtime type switch time_t second time = %ld.\n", t_time); 
    
    tm_ptr = localtime(&t_time);

    printf("time_t switch localtime type, the time is: \
            \n yday = %d \
            \n wday = %d \
            \n year = %d \
            \n mon =  %d \
            \n mday = %d \
            \n hour = %d \
            \n min =  %d \
            \n sec =  %d \
            \n isdst =%d.\n", 
            tm_ptr->tm_yday,
            tm_ptr->tm_wday,
            tm_ptr->tm_year,
            tm_ptr->tm_mon,
            tm_ptr->tm_mday,
            tm_ptr->tm_hour, 
            tm_ptr->tm_min, 
            tm_ptr->tm_sec,
            tm_ptr->tm_isdst
            );

    t_time = mktime(tm_ptr); /*重新转换为time_t类型的UTC时间，这里有一个时区的转换*/   
    printf("localtime type switch time_t third time = %ld.\n", t_time); 
}


string getCurTimeAndFormatOutput()
{
    //获取当前时间，并且以某种格式输出
    char buf[128];
    time_t t_time = time(NULL);
    //一年月日格式输出 [20171221]
    string timeFmt_1 = "%Y%m%d";
    struct tm* local = localtime(&t_time);
    strftime(buf, 64, timeFmt_1.c_str(), local);
    printf("--time format %%Y%%m%%y-- = %s.\n", buf);
    return buf;
}

string getCurTimeForMicroSecond()
{
    //strftime/snprintf 函数的使用,获取当前时间(微秒),并以某种格式输出
    char buf[128];
    char temp[128];
    struct tm          tmBuf;
    struct timeval     tv;
    struct timezone    tz;

    gettimeofday(&tv, &tz);
    string timeFmt_1 = "%Y%m%d";
    localtime_r(&tv.tv_sec, &tmBuf);
    strftime(buf, 64, timeFmt_1.c_str(), &tmBuf);

    //snprintf(buf, 64, "%s.%06ld", temp, tv.tv_sec, tv.tv_usec);
    snprintf(buf, 64, "%s.%ld.%06ld", temp, tv.tv_sec, tv.tv_usec);

    printf("--time format MicroSecond  %%Y%%m%%y-- = %s.\n", buf);
    return buf;
}
int main()
{
    getTimeIntervalForSeconds();
    getTimeIntervalForMicroseconds();
    tm2formatTimeString();
    timeString2tm();
    getCurTime2Microseconds();
    getTimeIntervalForMicroseconds();
    getCurTimeForMicroSecond();
    getCurTimeAndFormatOutput();
    time_t__2__tm_switch();
    getDiffTimezoneTime();
    
    return 0;
}
