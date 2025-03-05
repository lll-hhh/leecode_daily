#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        int minDistance(string word1, string word2) {
            if(word1.empty()&&word2.empty())return 0;
            if(word1.empty()||word2.empty())return max(word1.size(),word2.size());
            int st1=word1.size();
            int st2=word2.size();
            vector<vector<int>> dp(st1+1,vector<int>(st2+1,0));
    
            for(int i=0;i<=st1;i++){
                dp[i][0]=i;
            }
            for(int i=0;i<=st2;i++){
                dp[0][i]=i;
            }
            for(int i=1;i<=st1;i++){
                for(int j=1;j<=st2;j++){
                    if(word1[i-1]==word2[j-1]){
                        dp[i][j]=dp[i-1][j-1];
                    }
                    else {
                        dp[i][j]=min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
                    }
                }
            }
            return dp[st1][st2];
        }
    };