#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int climbStairs(int n) {
        if(n==0)return 0;
        vector<int> dp(n+1);
        dp[0]=1;dp[1]=1;
        for(int i=2;i<=n;i++)dp[i]=dp[i-1]+dp[i-2];
        return dp[n];
    }
};
//确定dp【i】含义:dp[i]为迈到第i阶的方法
//确定递推公式：dp【i】=dp【i-1】+dp【i-2】
//dp数组如何初始化:dp【0】=1,dp【1]=1
//遍历顺序，从前向后:
//打印dp数组:
int main(){
    Solution solu;
    cout<<solu.climbStairs(3);
}