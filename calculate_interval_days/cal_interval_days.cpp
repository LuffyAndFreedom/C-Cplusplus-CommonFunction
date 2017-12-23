#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

//思路,先计算从某个时间点到start time的天数, 再计算某个时间点(和前面同一个)到end time的天数, 再相减

/************************************************************************/  
/*    判断闰年函数(4年一润,100年不润,400年再润)                         */  
/************************************************************************/  

//判断是闰年的算法
bool isLeapYear(int y){
    return ((y % 4 == 0 && y % 100 != 0 )|| y % 400 == 0);
}

//计算输入某一年天数
int daysOfYear(int year){
    return isLeapYear(year) ? 366 : 365; 
}

//计算输入日期, 返回本月的天数
int daysOfMonth(int year, int month){
    if( month == 2 )
        return isLeapYear( year ) ? 29 : 28;
    else
        return ( month == 4 || month == 6 || month == 9 || month == 11 ) ? 30 : 31;
}

//计算输入日期, 返回本年已经过的天数
int daysBefore(int year, int month, int day){
    int result=0;
    for( int i = 1; i <= 12; i++ ) {
        if( i == month ) {
            result += day;
            return result;
        } else {
            result += daysOfMonth( year, i );   
        }   
    }
}

//判断输入日期的有效行
bool validDate(int year, int month, int day){
    if( year > 3000 || year < 1900 ) {
        printf("error year!\n");
        return false;
    }
    if( month > 12 || month < 1 ) {
        printf("error month!\n");
        return false;
    }
    if( day > daysOfMonth( year, month ) || day < 1 ) {
        printf("error day!\n");
        return false;
    }
    return true;
}

//计算1900年1月1号到输入时间的天数
int calculateDaysFrom1900(int year, int month, int day)
{
    int result = 0;
    for(int i = 1900; i <= year; i++) {
        result += daysOfYear( year );
    }
    return result + daysBefore( year, month, day);
}

//计算任意两个给定日期间相隔多少天
int calculateIntervalDate(string &startDate, string &endDate)
{
    int y1, m1, d1, y2, m2, d2;
    sscanf(startDate.c_str(), "%04d%02d%02d", &y1, &m1, &d1);
    sscanf(endDate.c_str(), "%04d%02d%02d", &y2, &m2, &d2);
    validDate( y1, m1, d1 );
    validDate( y2, m2, d2 );
    return calculateDaysFrom1900(y2, m2, d2) - calculateDaysFrom1900(y1, m1, d1);
}

int main(){
    string startDate("20171121");
    string endDate("20171229");
    printf("%d\n", calculateIntervalDate(startDate, endDate));
    return 0;
}
