#include <iostream>  
#include <string.h>
#include <stdlib.h>
using namespace std;  

//任意给定一组数据，和一个和值，求其中元素相加等于和值的结果集

int array[]={5,3,1,0,2,1,6,9,9,8};  
bool x[100]={false};//标记第i个元素是否已经使用  
int arrayNum = sizeof(array) / sizeof(array[0]);//元素个数  
int sum = 18;//目标和  
int curSum = 0;//当前和  
int cmp(const void *a,const void *b)  
{  
    return *(int *)b-*(int *)a;  
}  
void backtrace(int n)  
{  
    if(curSum > sum)  return ;  
    if(curSum == sum) {  
        for(int j=0; j<n; ++j) {  
            if(x[j])  
                cout<< "a = " << array[j]<<" ";  
        }  
        cout<<endl;  
        return;  
    }  
    if(n==arrayNum)//超过n层  
        return ;  
    for(int i=n; i < arrayNum; ++i)  
    {  
        if(x[i]==false)//未使用  
        {  
            x[i]=true;  
            curSum+=array[i];  
            backtrace(i+1);  
            x[i]=false;  
            curSum-=array[i];
            while(i < arrayNum-1 && array[i] == array[i+1]) ++i;
        }  
    }  
}
//回溯法遍历所有的组合, 得出符合条件的所有结果
//一层一层遍历下去, curSum当前总值 小于 目标值则继续计算下一个值,如果相等则打印符合条件的组合,如果不符合条件则回到上一层,继续遍历下一个值(穷尽法)
//给定数组的值可能有一些相同的值,所以结果集中要不包含相同的结果,可以对数组先进行排序,再进行过滤;
//过滤    while(i<arrayNum-1 && array[i]==array[i+1]) ++i;   当前值与下一个值相等时，跳过
int main()  
{  
    qsort(array, arrayNum, sizeof(array[0]), cmp);
    backtrace(0);  

    return 0;  
}  
//以第一个书为基准，遍历所有组合,
//比如三个数,遍历顺序。0、01、012、02、1、12、3
