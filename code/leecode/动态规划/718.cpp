#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        int findLength(vector<int>& nums1, vector<int>& nums2) {
            if(nums1.empty()||nums2.empty())return 0;
            int si1=nums1.size();
            int si2=nums2.size();
            vector<vector<int>> dp(si2+2,vector<int>(si1+2,0));
    
            int maxx=0;
            for(int i=si2-1;i>=0;i--){
                for(int j=si1-1;j>=0;j--){
                    dp[i][j]=
                    nums1[j]==nums2[i]?
                    dp[i+1][j+1]+1:0;
                    maxx=max(maxx,dp[i][j]);
                }
            }
            return maxx;
        }
    };
int main(){
    Solution solu;
    vector<int> lh{0,1,1,1,1};
    vector<int> lc{1,0,1,0,1};
    cout<<solu.findLength(lh,lc);
}