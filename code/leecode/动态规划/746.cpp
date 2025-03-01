#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        if(cost.empty()){
            return 0;
        }
        vector<int> dp(cost.size()+1);
        dp[0]=0;dp[1]=0;
        for(int i=2;i<=cost.size();i++){
            dp[i]=min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2]);
        }
        return dp[cost.size()];
    }
};
//确定dp【i】含义：第i阶最小代价
//确定递推公式：dp【i】=min（dp【i-1】+cost【i-1】，dp【i-2】+cost【i-2】）
//dp数组如何初始化:dp【0】=0,dp【1】=cost【0】
//遍历顺序，从前向后
//打印dp数组
int main(){
    Solution solu;
    vector<int> cost{10,15,20};
    cout<<solu.minCostClimbingStairs(cost);
}