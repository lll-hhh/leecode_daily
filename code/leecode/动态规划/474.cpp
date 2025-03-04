#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        if(strs.empty())return 0;
        int si=strs.size();
        vector<pair<int,int>> si01;
        vector<vector<vector<int>>> dp(si+1,vector<vector<int>>(n+2,vector<int>(m+2,0)));
        
        for(auto& a:strs){
            pair<int,int> lh={0,0};
            for(auto& b:a){
                if(b=='0')lh.first++;
                else if(b=='1')lh.second++;
            }
            si01.push_back(lh);
        }


        int maxx=-1;
        for(int i=1;i<=si01.size();i++){
            int zeros = si01[i - 1].first;
            int ones = si01[i - 1].second;
            for(int j=0;j<=n;j++){
                for(int k=0;k<=m;k++){
                    if(ones<=j&&zeros<=k)
                    dp[i][j][k]=max(dp[i-1][j][k],
                        dp[i-1][j-ones][k-zeros]+1);
                    else dp[i][j][k]=dp[i-1][j][k];
                    if(dp[i][j][k]>maxx)maxx=dp[i][j][k];
                }
            }
        }
        return maxx;
        
    }
};
int main(){
    vector<string> lh={"10","0001","111001","1","0"};
    Solution s;
    cout<<s.findMaxForm(lh,5,3);
}