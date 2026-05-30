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
public: // 公共成员，LeetCode 会调用这里的函数
    int pathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return 0;
        int ans = 0;

        ans += rootSum(root, targetSum);
        ans += pathSum(root->left, targetSum);
        ans += pathSum(root->right, targetSum);

        return ans;
    }

    int rootSum(TreeNode *root, long long targetSum)
    {
        int ans = 0;
        if (root->val == targetSum)
            ans += 1;
        if (root->left)
            ans += rootSum(root->left, targetSum - root->val);
        if (root->right)
            ans += rootSum(root->right, targetSum - root->val);
        return ans;
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