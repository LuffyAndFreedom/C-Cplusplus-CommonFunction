#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;
//sort，只能对连续内存的数据进行排序，像链表这样的结构是无法排序的。

struct node
{
    int a;
    int b;
    double c;
}arr[100];
//有一个node类型的数组node arr[100]，想对它进行排序：先按a值升序排列，如果a值相同，
//     再按b值降序排列，如果b还相同，就按c降序排列。就可以写这样一个比较函数。
bool cmp_struct(node x, node y)
{
    if(x.a!=y.a) return x.a<y.a;
    if(x.b!=y.b) return x.b>y.b;
    return x.c>y.c;
}
int array[] = {23, 34, 24, 9, 3, 12, 45, 46, 23, 9, 3, 75, 38};
bool cmp(int a, int b)
{
    return a>b;
}
void print()
{
    for(int i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}
int main()
{
    //默认排序，从小到大
    sort(array, array+sizeof(array)/sizeof(array[0]));
    print();
    //配合cmp函数,实现从大到小排序
    sort(array, array+sizeof(array)/sizeof(array[0]), cmp);
    print();
    return 0;
}
