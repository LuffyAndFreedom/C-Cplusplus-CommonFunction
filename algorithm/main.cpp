#include<iostream>
#include<math.h>
#include<stdio.h>
using namespace std;

int queenNum=8;
int total=0;
int pos[8];

void prinf_value()
{
    for(int i = 0; i < 8; i++) {
        printf("c[%d] = %d.\n", i, pos[i]);
    }
}

bool is_ok(int curRow) {
    for(int j=0;j!=curRow;j++) {
        if(pos[curRow]==pos[j] || curRow-pos[curRow]==j-pos[j] || curRow+pos[curRow]==j+pos[j]) { /* 检查横排(列)和对角线上是否可以放置皇后 */
            return false;
        }
    }
    return true;
}

void queen(int curRow) {
    if(curRow==queenNum) {
        total++;
        prinf_value();
    }
    else
        for(int col=0;col!=queenNum;col++){
            pos[curRow]=col;
            if(is_ok(curRow))
                queen(curRow+1);
        }       
}

int main(){
    queen(0);
    cout<<total;
    return 1;

}
