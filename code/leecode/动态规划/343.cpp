#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int integerBreak(int n) {
        if(n==0)return 0;
        vector<int> dp(n+2);
        dp[0]=0;
        dp[1]=1;
        dp[2]=1;
        dp[3]=2;
        for(int i=4;i<=n;i++){
            int max=-1;
            for(int j=1;j<=i;j++){
                if(max<(dp[j]>j?dp[j]:j)* (dp[i-j]>i-j?dp[i-j]:i-j))
                max=(dp[j]>j?dp[j]:j)* (dp[i-j]>i-j?dp[i-j]:i-j);
            }
            dp[i]=max;
        }
        return dp[n];
    }
};
//确定dp【i】含义:数i的最大乘积
//确定递推公式：dp【i】=dp【i-1】+dp【i-2】
//dp数组如何初始化:dp【0】=1,dp【1]=1
//遍历顺序，从前向后:
//打印dp数组:
int main(){
    int n=4;
    Solution sulo;
    cout<<sulo.integerBreak(n);
}