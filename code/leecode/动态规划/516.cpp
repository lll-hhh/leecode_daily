#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
        int longestPalindromeSubseq(string s) {
            if(s.empty())return 0;
            int si=s.size();
            vector<vector<int>> dp(si,vector<int>(si,0));
            for(int i=0;i<si;i++)dp[i][i]=1;
            
            int maxx=1;
            for(int ie=si,jb=1;ie;ie--,jb++){
                for(int i=0,j=jb;i<ie,j<si;i++,j++){
                    if(s[i]==s[j]){
                        if(i+1==j)dp[i][j]=2;
                        else dp[i][j]=dp[i+1][j-1]+2;
                        if(maxx<dp[i][j])maxx=dp[i][j];
                    }
                    else {
                        if(i+1==j)dp[i][j]=1;
                        else dp[i][j]=max(dp[i][j-1],dp[i+1][j]);
                    }
                }
            } 
            return maxx;
        }
    };
    int main(){
        Solution s;
        cout<<s.longestPalindromeSubseq("bbbb");
    }