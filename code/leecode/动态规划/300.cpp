#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty())return 0;
        else if(nums.size()==1)return 1;
        int si=nums.size();
        vector<int> dp(si,0);
        dp[0]=1;
        int  maxx=0;
        for(int i=1;i<si;i++){
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i])dp[i]=max(dp[i],dp[j]+1);
            }
            if(dp[i]==0)dp[i]=1;
            if(maxx<dp[i])maxx=dp[i];
        }
        return maxx;
    }
};
int main(){
    Solution solu;
    vector<int> lh{1,3,6,7,9,4,10,5,6};
    cout<<solu.lengthOfLIS(lh);
}