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
{       // 定义解题类
public: // 公共成员，LeetCode 会调用这里的函数
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    { // 在 root 这棵树中寻找 p 和 q 的最近公共祖先
        if (!root || root == p || root == q)
            return root;
        TreeNode *zuo = lowestCommonAncestor(root->left, p, q);
        TreeNode *you = lowestCommonAncestor(root->right, p, q);

        if (zuo && you)
            return root;
        if (zuo)
            return zuo;
        if (you)
            return you;
        return nullptr;
    } // 函数结束
}; // 类结束
int main()
{
    Solution liuhao;
    int a = 0;
    cin >> a;

    system("pause"); // 添加这行代码让黑框停留
    return 0;
}