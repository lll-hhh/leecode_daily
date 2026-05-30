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

class Solution {
private:
    stack<TreeNode*> liuhao;
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return; // 解决 Bug 1: 边界处理

        liuhao.push(root);
        
        // 引入一个虚拟指针，用来帮我们串联链表
        // 它的 right 会指向我们第一个弹出来的节点（即真正的 root）
        TreeNode* dummy = new TreeNode(0);
        TreeNode* prev = dummy;

        while (!liuhao.empty()) {
            TreeNode* curr = liuhao.top();
            liuhao.pop();

            // 1. 核心安全操作：先辈们（子节点）赶紧入栈“存档”，防止接下来被斩断
            if (curr->right != nullptr) {
                liuhao.push(curr->right);
            }
            if (curr->left != nullptr) {
                liuhao.push(curr->left);
            }

            // 2. 串联链表结构
            prev->right = curr;  // 上一个节点的右边指向当前节点
            prev->left = nullptr; // 左边必须严格清空
            prev = curr;         // prev 指针后移，传给下一轮
        }

        // 清理临时申请的虚拟节点内存
        delete dummy;
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