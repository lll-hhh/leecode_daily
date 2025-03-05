#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minDistance(string word1, string word2) {
        if(word1.empty()||word2.empty())return 0;
        int st1=word1.size();
        int st2=word2.size();
        vector<vector<int>> dp(st1+1,vector<int>(st2+1,0));
        for(int i=1;i<=st1;i++){
            for(int j=1;j<=st2;j++){
                if(word1[i-1]==word2[j-1])dp[i][j]=dp[i-1][j-1]+1;
                else dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
            }
        }
        return max(st1,st2)-dp[st1][st2];
    }
};