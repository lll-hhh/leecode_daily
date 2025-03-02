#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        if(nums.empty())return 0;

        int sum=accumulate(nums.begin(),nums.end(),0);
        int tar = sum - target;
        if (tar < 0 || tar % 2 != 0) {
            return 0;
        }
        tar/=2;
        int si=nums.size();

        vector<vector<int>> dp(si+1,vector<int>(tar+1,0));

        dp[0][0]=1;

        for(int i=1;i<=si;i++){
            for(int j=0;j<=tar;j++){
                dp[i][j]=dp[i-1][j];
                if(j>=nums[i-1])
                    dp[i][j]+=dp[i-1][j-nums[i-1]];
                
            }
        }
        return dp[si][tar];

    }
};
int main(){
    Solution solu;
    vector<int> lh{1,1,1,1,1};
    cout<<solu.findTargetSumWays(lh,3);
}