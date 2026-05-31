#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {                     // 返回字符串 s 中最长的回文子串
        int n = s.size(); // 获取字符串长度

        int start = 0;  // 记录最长回文子串的起始位置
        int maxLen = 1; // 记录最长回文子串的长度，至少有 1 个字符

        for (int i = 0; i < n; i++)
        {                                   // 枚举每一个位置作为回文中心
            int len1 = expand(s, i, i);     // 以 i 为中心，找奇数长度回文
            int len2 = expand(s, i, i + 1); // 以 i 和 i+1 中间为中心，找偶数长度回文

            int len = max(len1, len2); // 当前中心能扩出来的最长长度

            if (len > maxLen)
            {                              // 如果当前长度比之前记录的最长还长
                maxLen = len;              // 更新最长长度
                start = i - (len - 1) / 2; // 根据中心 i 和长度 len 算出起点
            } // if 结束
        } // for 结束

        return s.substr(start, maxLen); // 从 start 开始截取 maxLen 长度的子串
    } // longestPalindrome 函数结束

    int expand(string &s, int left, int right)
    { // 从 left 和 right 开始向两边扩展，返回回文长度
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {            // 没越界且左右字符相等，就继续扩
            left--;  // 左边往左走
            right++; // 右边往右走
        } // while 结束

        return right - left - 1; // 返回回文长度，因为退出时 left 和 right 已经多走了一步
    } // expand 函数结束
}; // Solution 类结束

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int n = s.size();

        vector<vector<bool>> dp(n, vector<bool>(n, false));

        int start = 0;
        int maxLen = 1;

        for (int len = 1; len < n; len++)
        {
            for (int i = 0; i < n - len - 1; i++)
            {
                int j = i + len - 1;
                if (s[i] == s[j])
                {
                    if (len <= 3 || dp[i + 1][j - 1] == 1)
                    {
                        dp[i][j] = 1;
                        if (len > maxLen)
                        {
                            start = i;
                            maxLen = len;
                        }
                    }
                }
            }
        }
        return s.substr(start, maxLen);
    }
};