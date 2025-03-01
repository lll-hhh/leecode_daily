#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int numTrees(int n) {
        if(n==0)return 0;
        vector<int> dp(n+3);
        dp[0]=1;
        dp[1]=1;
        dp[2]=2;
        for(int i=3;i<=n;i++){
            int sum=0;
            for(int j=0;j<i;j++){
                if(j==i-j-1){
                    sum+=dp[j]*dp[j];
                    continue;
                }
                sum+=dp[j]*dp[i-j-1];
            }
            dp[i]=sum;
        }
        return dp[n];
    }
};
int main(){
    Solution solu;
    cout<<solu.numTrees(3);
}
//确定dp【i】含义:i个节点的二叉树个数
//确定递推公式：dp【i】=sum（dp【j】，dp【i-j】）j=1,2,3,4......i
//dp数组如何初始化:dp【1】=1,dp【2]=2
//遍历顺序，从前向后:
//打印dp数组: