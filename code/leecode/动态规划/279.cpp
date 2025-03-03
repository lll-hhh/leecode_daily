#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numSquares(int n) {
        if(n==0)return 0;
        vector<int> numbers;
        for(int i=1;i*i<=n;i++)numbers.push_back(i*i);
        int nums=numbers.size();
        vector<vector<int>> dp(nums+2,vector<int>(n+2,0));
        for(int i=0;i<=n;i++)dp[0][i]=i;
        for(int i=1;i<nums;i++){
            for(int j=1;j<=n;j++){
                if(j<numbers[i]){
                    dp[i][j]=dp[i-1][j];
                }else
                dp[i][j]=min(dp[i][j-numbers[i]]+1,dp[i-1][j]);
            }
        }
        return dp[nums-1][n];
    }
};
int main(){
    Solution s;
    cout<<s.numSquares(12);
}