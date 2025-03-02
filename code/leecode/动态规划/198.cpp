#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty())return 0;
        if(nums.size()==1)return nums[0];
        int si=nums.size();
        vector<int> dp(si+2,0);
        dp[0]=nums[0];
        dp[1]=max(nums[0],nums[1]);
        int maxx=dp[0];
        for(int i=2;i<si;i++){
            dp[i]=max(dp[i-1],dp[i-2]+nums[i]);
        }
        return dp[si-1];
    }
};
int main(){
    Solution solu;
    vector<int> lh{1,2,3,1};
    cout<<solu.rob(lh);
}