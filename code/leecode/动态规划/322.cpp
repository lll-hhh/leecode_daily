#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) { // 主函数，coins 是硬币数组，amount 是目标金额
        vector<int> dp(amount + 1, amount + 1); // dp[i] 表示凑出金额 i 最少需要几个硬币，初始设为不可能的大数

        dp[0] = 0; // 凑出金额 0 需要 0 个硬币

        for (int i = 1; i <= amount; i++) { // 枚举每一个金额，从 1 到 amount
            for (int coin : coins) { // 枚举每一种硬币
                if (i - coin < 0) { // 如果当前金额 i 比硬币 coin 小，说明不能用这个硬币
                    continue; // 跳过这个硬币
                } // if 结束

                dp[i] = min(dp[i], dp[i - coin] + 1); // 选择使用 coin：先凑出 i-coin，再加上当前这 1 枚硬币
            } // 内层 for 结束
        } // 外层 for 结束

        if (dp[amount] == amount + 1) { // 如果最后还是初始大数，说明凑不出 amount
            return -1; // 按题目要求返回 -1
        } // if 结束

        return dp[amount]; // 返回凑出 amount 的最少硬币数量
    } // coinChange 函数结束
}; // Solution 类结束

int main(){
    Solution solu;
    vector<int> lh{3,5,6};
    cout<<solu.coinChange(lh,17);
}