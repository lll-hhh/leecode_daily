#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countSubstrings(string s) {
        if(s.empty())return 0;
        int si=s.size();
        vector<vector<int>> dp(si,vector<int>(si,0));
        //ij
        int sum=si;
        for(int i=0;i<si;i++)dp[i][i]=1;

        int ie=si;
        int jb=1;
        for(;ie;ie--,jb++){
            for(int i=0,j=jb;i<ie,j<si;i++,j++){
                if(s[i]==s[j]&&(i+1==j||dp[i+1][j-1])){
                    dp[i][j]=1;
                    sum++;
                }
                else {
                    dp[i][j]=0;
                }
            }
        }

        // for(int i=0;i<si;i++){
        //     for(int j=i+1;j<si;j++){
        //         if(s[i]==s[j]&&(i+1==j||dp[i+1][j-1])){
        //             dp[i][j]=1;
        //             sum++;
        //         }
        //         else {
        //             dp[i][j]=0;
        //         }
        //     }
        // }
        return sum;
    }
};
int main(){
    Solution s;
    cout<<s.countSubstrings("aaaaa");
}