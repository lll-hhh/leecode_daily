#include <bits/stdc++.h>
using namespace std;
class Solution
{                               // 定义 LeetCode 要求的 Solution 类
public:                         // 下面的成员函数和变量可以被外部访问
    vector<vector<string>> ans; // 存放最终答案，每个答案是一组字符串切分
    vector<string> path;        // 存放当前正在尝试的一种切分方案

    vector<vector<string>> partition(string s)
    { // 主函数，传入字符串 s，返回所有回文切分方案
        dfs(s, 0);
        return ans;
    }

    void dfs(string &s, int start)
    { // 回溯函数，start 表示当前从哪里开始切
        if (start == s.size())
        {                        // 如果 start 到达字符串末尾，说明整个字符串已经切完
            ans.push_back(path); // 把当前这一组切分方案加入答案
            return;              // 结束当前递归
        } // if 结束

        for (int end = start; end < s.size(); end++)
        { // 枚举当前这一刀切到哪里
            if (!check(s, start, end))
                continue; // 如果 s[start...end] 不是回文串，就跳过

            path.push_back(s.substr(start, end - start + 1)); // 把当前回文子串加入 path

            dfs(s, end + 1); // 继续从 end + 1 的位置往后切

            path.pop_back(); // 回溯，撤销刚才加入的子串，尝试下一种切法
        } // for 循环结束
    } // dfs 函数结束

    bool check(string &s, int l, int r)
    { // 判断 s[l...r] 是否是回文串
        while (l < r)
        { // 只要左指针还在右指针左边，就继续比较
            if (s[l] != s[r])
                return false; // 如果左右字符不同，说明不是回文串
            l++;              // 左指针向右移动
            r--;              // 右指针向左移动
        } // while 循环结束

        return true; // 所有字符都匹配，说明是回文串
    } // check 函数结束
}; // Solution 类结束