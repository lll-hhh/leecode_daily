#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty()||nums2.empty())return 0;
        int st1=nums1.size();
        int st2=nums2.size();
        vector<vector<int>> dp(st1+1,vector<int>(st2+1,0));
        for(int i=1;i<=st1;i++){
            for(int j=1;j<=st2;j++){
                if(nums1[i-1]==nums2[j-1])dp[i][j]=dp[i-1][j-1]+1;
                else dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
            }
        }
        return dp[st1][st2];
    }
};