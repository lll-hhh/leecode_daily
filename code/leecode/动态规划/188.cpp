#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.empty())return 0;
        vector<vector<int>> dp(k*2+1,vector<int>(prices.size(),0));
        for(int i=1;i<k*2+1;i+=2){
            dp[i][0]=-prices[0];
        }

        for(int i=1;i<prices.size();i++){
            for(int j=1;j<k*2+1;j++){
                if(j%2==1){
                    dp[j][i]=max(dp[j][i-1],dp[j-1][i-1]-prices[i]);
                }else if(j%2==0){
                    dp[j][i]=max(dp[j][i-1],dp[j-1][i-1]+prices[i]);
                }
            }
        }

        int maxx=-1;
        for(int i=0;i<k*2+1;i++){
            if(maxx<dp[i][prices.size()-1])
                maxx=dp[i][prices.size()-1];
        }

        return maxx;
    }
};
int main(){
    Solution s;
    vector<int> lh{2,4,1};
    cout<<s.maxProfit(2,lh);
}