#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        auto words=unordered_set<string>();
        for(auto& a:wordDict){
            words.insert(a);
        }

        auto dp=vector<bool> (s.size()+1);
        dp[0]=true;

        for(int i=1;i<=s.size();i++){
            for(int j=0;j<i;j++){
                if(dp[j] && words.find(s.substr(i,i-j))!=words.end()){
                    dp[j]=true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};