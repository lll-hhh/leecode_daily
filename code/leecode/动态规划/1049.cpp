#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        if(stones.empty())return 0;
        if(stones.size()==2){
            return stones[0]>stones[1]?stones[0]-stones[1]:stones[1]-stones[0];
        }
        int sum =0;
        for(auto& a:stones)sum+=a;
        int si=sum/2;
        vector<vector<int>> dp(stones.size(),vector<int>(si+1,0));
        
        for(int i=0;i<si;i++){
            if(i==stones[0])dp[0][i]=1;
        }
        for(int i=0;i<stones.size();i++){
            dp[i][0]=1;
        }
        
        int max=0;

        for(int i=1;i<stones.size();i++){
            for(int j=1;j<=si;j++){
                if(stones[i]>j)dp[i][j]=dp[i-1][j];
                else{
                    for(int k=0;k<=i-1;k++){
                        if(dp[k][j-stones[i]]==1){
                            dp[i][j]=1;
                            if(max<j)max=j;
                        }
                    }
                }
            }
        }
        
        return sum-max*2;
    }
};
int main(){
    Solution solu;
    vector<int> lh{1,2};
    cout<<solu.lastStoneWeightII(lh);
}