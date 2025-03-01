#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int fib(int n) {
        if(n<=0)return 0;
        vector<int> lh(n+1);
        lh[0]=1;lh[1]=1;
        for(int i=2;i<n;i++)
            lh[i]=lh[i-1]+lh[i-2];
        return lh[n-1];
    }
};
//确定dp【i】含义，第i个斐波那契数的值为dp【i】
//确定递推公式：dp【i】=dp【i-1】+dp【i-2】
//dp数组如何初始化dp【0】=1;dp【1】=1
//遍历顺序，从前向后
//打印dp数组
int main(){
    Solution solu;
    cout<<solu.fib(5);
}