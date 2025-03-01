#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    int bugs01(vector<int> &value,vector<int> &size,int kind,int bugs){
        if(value.empty()||size.empty()){
            return 0;
        }
        vector<vector<int>> dp(kind+1,vector<int>(bugs+1,0));
        for(int i=1;i<=kind;i++){
            for(int j=0;j<=bugs;j++){
                if(size[i-1]>j)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j]=max(dp[i-1][j],dp[i-1][j-size[i-1]]+value[i-1]);
            }
        }
        int maxx=0;
        for(int i=1;i<=kind;i++){
            for(int j=0;j<=bugs;j++){
                if(dp[i][j]>maxx)maxx=dp[i][j];
            }
        }
        return maxx;
    }

};

int main(){
    int kind,bugs;
    cin>>kind>>bugs;
    vector<int> value(kind);
    vector<int> size(kind);
    for(int i=0;i<kind;i++){
        cin>>size[i];
    }
    for(int i=0;i<kind;i++){
        cin>>value[i];
    }
    Solution sulo;
    cout<<sulo.bugs01(value,size,kind,bugs);
}