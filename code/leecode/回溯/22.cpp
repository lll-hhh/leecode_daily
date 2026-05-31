#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<string> ans;
    string path;
    vector<string> generateParenthesis(int n)
    {
        dfs(n, 0, 0);
        return ans;
    }
    void dfs(int n, int left, int right)
    {
        if (n * 2 == path.size())
        {
            ans.push_back(path);
            return;
        }
        if (left < n)
        {
            path.push_back('(');
            dfs(n, left + 1, right);
            path.pop_back();
        }
        if (right < left)
        {
            path.push_back(')');
            dfs(n, left, right + 1);
            path.pop_back();
        }
    }
};