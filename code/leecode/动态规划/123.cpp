#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty())return 0;
        vector<vector<int>> dp(5,vector<int>(prices.size(),0));
        dp[0][0]=0;
        dp[1][0]=-prices[0];
        dp[2][0]=0;
        dp[3][0]=-prices[0];
        dp[4][0]=0;
        for(int i=1;i<prices.size();i++){
            dp[0][i]=dp[0][i-1];
            dp[1][i]=max(dp[1][i-1],dp[0][i-1]-prices[i]);
            dp[2][i]=max(dp[2][i-1],dp[1][i-1]+prices[i]);
            dp[3][i]=max(dp[3][i-1],dp[2][i-1]-prices[i]);
            dp[4][i]=max(dp[4][i-1],dp[3][i-1]+prices[i]);
        }
        int maxx=0;
        for(int i=0;i<5;i++){
            if(maxx<dp[i][prices.size()-1])maxx=dp[i][prices.size()-1];
        }
        return maxx;
    }
};