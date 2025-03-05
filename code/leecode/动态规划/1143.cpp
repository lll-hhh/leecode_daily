#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if(text1.empty()||text2.empty())return 0;
        int st1=text1.size();
        int st2=text2.size();
        vector<vector<int>> dp(st2+1,vector<int>(st1+1,0));
        int flag=0;
        for(int i=0;i<st1;i++){
            if(text1[i]==text2[0])flag=1;
            dp[0][i]=flag;
        }
        flag=0;
        for(int i=0;i<st2;i++){
            if(text2[i]==text1[0])flag=1;
            dp[i][0]=flag;
        }
        for(int i=1;i<st2;i++){
            for(int j=1;j<st1;j++){
                if(text2[i]==text1[j])
                    dp[i][j]=dp[i-1][j-1]+1;
                else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
        return dp[st2-1][st1-1];
    }
};
int main(){
    string lh="abcde";
    string lc="ace";
    Solution s;
    cout<<s.longestCommonSubsequence(lh,lc);
}