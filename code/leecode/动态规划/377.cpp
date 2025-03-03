#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        if(nums.empty())return 0;
        sort(nums.begin(),nums.end());
        vector<__int64_t> dp(target+2,0);
        dp[0]=1;
        for(int i=0;i<=target;i++){
            for(int j=0;j<nums.size()&&nums[j]<=i;j++)
            dp[i]+=dp[i-nums[j]];
        }
        return dp[target];
    }
};
int main(){
    Solution solu;
    vector<int> lh{3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    cout<<solu.combinationSum4(lh,10);
}