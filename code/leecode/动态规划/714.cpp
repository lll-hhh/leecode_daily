#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        if(prices.empty())return 0;
        vector<vector<int>> dp(2,vector<int>(prices.size(),0));
        dp[0][0]=0;
        dp[1][0]=-prices[0];
        for(int i=1;i<prices.size();i++){
           dp[0][i]=max(dp[0][i-1],dp[1][i-1]+prices[i]-fee);
           dp[1][i]=max(dp[1][i-1],dp[0][i-1]-prices[i]);
        }
        return max(dp[0][prices.size()-1],dp[1][prices.size()-1]);
    }
};
int main(){
    Solution solu;
    vector<int> lh{1,3,2,8,4,9};
    cout<<solu.maxProfit(lh,2);
}