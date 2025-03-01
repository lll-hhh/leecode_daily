#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m==0&&n==0)return 0;
        vector<vector<int>> dp(m,vector<int>(n));
        for(auto& a:dp[0])a=1;
        for(auto& b:dp)b[0]=1;
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};
//确定dp【i】含义：
//确定递推公式：
//dp数组如何初始化:
//遍历顺序，从前向后
//打印dp数组
int main(){
    Solution solu;
    int m=3,n=7;
    cout<<solu.uniquePaths(m,n);
}