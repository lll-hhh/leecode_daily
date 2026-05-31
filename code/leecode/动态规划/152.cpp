#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {                         // 返回乘积最大的连续子数组乘积
        int maxVal = nums[0]; // maxVal 表示以当前位置结尾的最大乘积
        int minVal = nums[0]; // minVal 表示以当前位置结尾的最小乘积
        int ans = nums[0];    // ans 表示全局最大乘积答案

        for (int i = 1; i < nums.size(); i++)
        { // 从第二个数字开始遍历
            int omax = maxVal;
            int omin = minVal;
            maxVal = max(nums[i], max(omax * nums[i], omin * nums[i]));
            minVal = min(nums[i], min(omax * nums[i], omin * nums[i]));
            ans = max(ans, maxVal);
        } // for 结束

        return ans; // 返回全局最大乘积
    } // 函数结束
}; // 类结束