#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty())return 0;
        if(nums.size()==1)return nums[0];
        vector<int> dp(nums.size(),0);
        dp[0]=nums[0];
        int maxx=dp[0];
        for(int i=1;i<nums.size();i++){
            dp[i]=max(dp[i-1]+nums[i],nums[i]);
            maxx=max(dp[i],maxx);
        }
        return maxx;
    }
};


//         if(nums.size()==1)return nums[0];
//         vector<int> num(nums.size(),0);
//         num[0]=nums[0];
//         for(int i=0;i<nums.size()-1;i++){
//             num[i+1]=(nums[i+1]+num[i]);
//         }
//         for(int i=0;i<nums.size();i++){
//             num[i]+=10000;
//         }
//         vector<vector<int>> dp(2,vector<int>(nums.size(),0));
//         dp[0][0]-=num[0];
//             for(int j=1;j<nums.size();j++){
//                 dp[0][j]=max(dp[1][j-1]-num[j],dp[0][j]);
//                 dp[1][j]=max(dp[0][j-1]+num[j],dp[1][j]);
//             }
//         return max(dp[1][nums.size()-1],dp[0][nums.size()-1])-10000;
int main(){
    Solution solu;
    vector<int> lh{-2,1};
    cout<<solu.maxSubArray(lh);
}