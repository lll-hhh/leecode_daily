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

// class Solution
// {
// public:
//     TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
//     {
//         if (t1 == nullptr) {
//             return t2;
//         }
//         if (t2 == nullptr) {
//             return t1;
//         }
//         auto merged = new TreeNode(t1->val + t2->val);
//         merged->left = mergeTrees(t1->left, t2->left);
//         merged->right = mergeTrees(t1->right, t2->right);
//         return merged;
//     }
// };

class Solution
{
public:
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
    {
        if (t1 == nullptr)
            return t2;
        if (t2 == nullptr)
            return t1;
        auto merge = new TreeNode(t1->val + t2->val);
        auto queue1 = queue<TreeNode *>();
        auto queue2 = queue<TreeNode *>();
        auto q = queue<TreeNode *>();
        q.push(merge);
        queue1.push(t1);
        queue2.push(t2);
        while (!queue1.empty() && !queue2.empty())
        {
            auto node = q.front();
            auto node1 = queue1.front();
            auto node2 = queue2.front();
            q.pop();
            queue1.pop();
            queue2.pop();
            auto left1 = node1->left, left2 = node2->left, right1 = node1->right, right2 = node2->right;
            if (left1 != nullptr || left2 != nullptr)
            {
                if (left1 != nullptr && left2 != nullptr)
                {
                    auto left = new TreeNode(left1->val + left2->val);
                    node->left = left;
                    q.push(left);
                    queue1.push(left1);
                    queue2.push(left2);
                }
                else if (left1 != nullptr)
                {
                    node->left = left1;
                }
                else if (left2 != nullptr)
                {
                    node->left = left2;
                }
            }
            if (right1 != nullptr || right2 != nullptr)
            {
                if (right1 != nullptr && right2 != nullptr)
                {
                    auto right = new TreeNode(right1->val + right2->val);
                    node->right = right;
                    q.push(right);
                    queue1.push(right1);
                    queue2.push(right2);
                }
                else if (right != nullptr)
                {
                    node->right = right1;
                }
                else
                {
                    node->right = right2;
                }
            }
        }
        return merge;
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