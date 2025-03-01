#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty()){return 0;}
        int n=obstacleGrid.size();
        int m=obstacleGrid[0].size();
        vector<vector<int>> dp(n,vector<int>(m,0));
        for(int i=0;i<m;i++){
            if(obstacleGrid[0][i]==1)break;
            dp[0][i]=1;
        }
        for(int i=0;i<n;i++){
            if(obstacleGrid[i][0]==1)break;
            dp[i][0]=1;
        }
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(obstacleGrid[i][j]==1)continue;
                if(obstacleGrid[i-1][j]==1&&obstacleGrid[i][j-1]==1){
                    dp[i][j]=0;
                }
                else if(obstacleGrid[i-1][j]==1&&obstacleGrid[i][j-1]==0){
                    dp[i][j]=dp[i][j-1];
                }
                else if(obstacleGrid[i-1][j]==0&&obstacleGrid[i][j-1]==1){
                    dp[i][j]=dp[i-1][j];
                }
                else if(obstacleGrid[i-1][j]==0&&obstacleGrid[i][j-1]==0){
                    dp[i][j]=dp[i-1][j]+dp[i][j-1];
                }
            }
        }
        return dp[n-1][m-1];
    }
};
//确定dp【i】含义：
//确定递推公式：
//dp数组如何初始化:
//遍历顺序，从前向后
//打印dp数组
int main(){
    Solution solu;
    vector<vector<int>> lh{{0,0,0}};
    cout<<solu.uniquePathsWithObstacles(lh);
}