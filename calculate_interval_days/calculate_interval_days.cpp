#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

//思路,先计算从某个时间点到start time的天数, 再计算某个时间点(和前面同一个)到end time的天数, 再相减

//判断是闰年的算法
/************************************************************************/  
/*    判断闰年函数(4年一润,100年不润,400年再润)                         */  
/************************************************************************/  
bool isLeapYear(int y){
    return ((y % 4 == 0 && y % 100 != 0 )|| y % 400 == 0);
}
//计算从0年到当前年月日的天数
int sum(int y, int m, int d){
    int md[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31  };
    //假设从0年开始，也就是你不知道的第一天， 比如求x-y就等于求(x-0)-（y-0）
    int cnt = y * 365;
    //下面是求闰年二月份多一天的算法
    cnt += (y - 1) / 4 + 1;
    cnt -= (y - 1) / 100 + 1;
    cnt += (y - 1) / 400 + 1;
    //这是求这y年开始到m月d日多少天
    for (int i = 1; i < m; ++i) cnt += md[i];
    if (m > 2 && isLeapYear(y)) ++cnt;
    cnt += d;
    return cnt;
}
//计算任意两个给定日期间相隔多少天
int calculateIntervalDate(string &startDate, string &endDate)
{
    int y1, m1, d1, y2, m2, d2;
    sscanf(startDate.c_str(), "%04d%02d%02d", &y1, &m1, &d1);
    sscanf(endDate.c_str(), "%04d%02d%02d", &y2, &m2, &d2);
    return sum(y2, m2, d2) - sum(y1, m1, d1);
}

int main(){
    string startDate("20171121");
    string endDate("20171219");
    printf("%d\n", calculateIntervalDate(startDate, endDate));
    return 0;
}
