#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//qsort，只能对连续内存的数据进行排序，像链表这样的结构是无法排序的。
/*
     qsort（基本快速排序的方法，每次把数组分成两部分和中间的一个划分值，而对于有多个重复值的数组来说，基本快速排序的效率较低，且不稳定）。
        集成在C语言库函数里面的的qsort函数，使用 三 路划分的方法解决排序这个问题。
        所谓三路划分，是指把数组划分成小于划分值，等于划分值和大于划分值的三个部分。
    
    void qsort( void *base, size_t num, size_t width, int (__cdecl *compare )
    int compare (const void *elem1, const void *elem2 ) );

    qsort（即，quicksort）主要根据你给的比较条件给一个快速排序，主要是通过指针移动实现排序功能。排序之后的结果仍然放在原来数组中。
    第一个参数 base 是 需要排序的目标数组名（或者也可以理解成开始排序的地址，因为可以写&s[i]这样的表达式）
    第二个参数 num 是 参与排序的目标数组元素个数
    第三个参数 width 是单个元素的大小（或者目标数组中每一个元素长度），推荐使用sizeof(s[0]）这样的表达式
    第四个参数 compare 就是让很多人觉得非常困惑的比较函数啦。)
        假设是对int排序的话，如果是升序，那么就是如果a比b大返回一个正值，小则负值，相等返回0，其他的依次类推。
 *
 * */

//对结构体一级排序
struct In
{
    double data;
    int other;
}s[100];

//cmp函数的入参一定是 const void* 类型
int cmp(const void* a, const void* b) 
{
    //整形排序
    return *(int *)a - *(int *)b;//升序排序
    //return *(int *)b - *(int *)a; //降序排序
    /*可见：参数列表是两个空指针，现在他要去指向你的数组元素。所以转型为你当前的类型，然后取值。
     *         升序排列时，若第一个参数指针指向的"值"大于第二个参数指针指向的"值"，则返回正；若第一个参数指针指向的"值"等于第二个参数指针指向的"值"，
     *             则返回零；若第一个参数指针指向的"值"小于第二个参数指针指向的"值"，则返回负。
     *             降序排列时，则刚好相反。
    */

    //char类型数组排序
    //return *(char *)a - *(char *)b; //升序排序
    //return *(char *)b - *(char *)a; //降序排序
    
    //double类型的数组排序
    //return *(double *)a - *(double *)b ? 1 : -1; //升序排序
    //return *(double *)a - *(double *)b ? -1 : 1; //降序排序
    
    //针对上面结构体In排序
    //return (*(In *)a).data > (*(In *)b).data ? 1 : -1;
    //如果 data 相同条件下，要按other排序，则可以加一个判断条件,相等情况下判断other大小
    
    //其余排序可以举一反三
}


int array[] = {23, 34, 24, 9, 3, 12, 45, 46, 23, 9, 3, 75, 38};
void print()
{
    for(int i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main()
{
    //整形排序
    qsort(array, sizeof(array)/sizeof(array[0]), sizeof(array[0]), cmp);
    print();
    return 0;
}
