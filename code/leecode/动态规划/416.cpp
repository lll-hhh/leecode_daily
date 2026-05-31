#include<bits/stdc++.h>
using namespace std;
// class Solution {
// public:
//     bool canPartition(vector<int>& nums) {
//         if(nums.empty())return false;
//         int sum=0;
//         for(auto& a:nums)sum+=a;
//         if(sum%2==1)return false;
//         vector<vector<int>> dp(nums.size(),vector<int>(sum/2+1,0));
//         for(int i=0;i<nums.size();i++)dp[i][0]=1;
//         dp[0][nums[0]]=1;
//         for(int i=1;i<nums.size();i++){
//             for(int j=1;j<=sum/2;j++){
//                 if(j<nums[i]){
//                     dp[i][j]=dp[i-1][j];
//                 }
//                 else {
//                     for(int k=0;k<i;k++)
//                     if(dp[k][j-nums[i]]==1)
//                     dp[i][j]=1;
//                 }
//                 if(j==sum/2&&dp[i][j]==1){
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
// };
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if(nums.empty())return 0;
        int sum=0;
        for(auto& a:nums)sum+=a;
        if(sum%2==1)return 0;
        int tg=sum/2;

        vector<vector<int>> dp(nums.size(),vector<int>(tg+2,0));

        if(nums[0]<=tg)dp[0][nums[0]]=1;

        for(int i=1;i<nums.size();i++){
            for(int j=0;j<=tg;j++){
                dp[i][j]=dp[i-1][j];
                if(nums[i]<=j)
                    dp[i][j]=dp[i][j]||dp[i-1][j-nums[i]];
                if(j==tg&&dp[i][j]==1)return 1;
            }
        }

        return 0;
    }
};
int main(){
    Solution solu;
    vector<int> lh{1,5,11,5};
    cout<<solu.canPartition(lh);
}