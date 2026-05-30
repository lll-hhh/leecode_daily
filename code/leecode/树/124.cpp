#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int ans;
    int maxPathSum(TreeNode *root)
    {
        ans = -INT_MAX;
        dfs(root);
        return ans;
    }
    int dfs(TreeNode *root)
    {
        if (!root)return 0;

        int zuo = max(0,dfs(root->left));
        int you = max(0,dfs(root->right));

        int zong = zuo + you + root->val;
        ans = max(ans, zong);

        return root->val + max(zuo, you);
    }
};

int main()
{
    Solution liuhao;
    int a = 0;
    cin >> a;

    system("pause"); // 添加这行代码让黑框停留
    return 0;
}