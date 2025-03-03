#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(coins.empty())return -1;
        if(amount==0)return 0;

        sort(coins.begin(),coins.end());

        vector<vector<int>> dp(coins.size(),vector<int>(amount+1,0));

        dp[coins.size()-1][amount]=-1;
        for(int i=1;i<=amount;i++){
            if(i%coins[0]==0)
            dp[0][i]=i/coins[0];
            else dp[0][i]=-1;
        }

        for(int i=1;i<coins.size();i++){
            for(int j=1;j<=amount;j++){
                if(j<coins[i])dp[i][j]=dp[i-1][j];
                else {
                    if(dp[i-1][j]!=-1&&dp[i][j-coins[i]]!=-1)dp[i][j]=min(dp[i-1][j],dp[i][j-coins[i]]+1);
                    else if(dp[i-1][j]!=-1&&dp[i][j-coins[i]]==-1)dp[i][j]=dp[i-1][j];
                    else if(dp[i-1][j]==-1&&dp[i][j-coins[i]]!=-1)dp[i][j]=dp[i][j-coins[i]]+1;
                    else dp[i][j]=-1;
                }
            }
        }

        return dp[coins.size()-1][amount];
    }
};

int main(){
    Solution solu;
    vector<int> lh{3,5,6};
    cout<<solu.coinChange(lh,17);
}