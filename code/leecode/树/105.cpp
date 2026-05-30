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
    unordered_map<int, int> liuhao;

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    { // 主函数：根据前序和中序数组构造二叉树
        for (int i = 0; i < preorder.size(); i++)
        {
            for (int j = 0; j < preorder.size(); j++)
            {
                if (inorder[j] == preorder[i])
                    liuhao[preorder[i]]=j;
            }
        }
        return build(preorder, 0, preorder.size() - 1, inorder, 0, preorder.size() - 1);
    } // buildTree 函数结束

    TreeNode *build(vector<int> &preorder, int preL, int preR, vector<int> &inorder, int inL, int inR)
    {
        if(preL>preR)return nullptr;
        TreeNode* root=new TreeNode(preorder[preL]);
        int fenge=liuhao[preorder[preL]];
        int geshu=fenge-inL;
        root->left=build(preorder,preL+1,preL+geshu,inorder,inL,inL+geshu-1);
        root->right=build(preorder,preL+geshu+1,preR,inorder,inL+geshu+1,inR);
        return root;
    }
}; // Solution 类结束
int main()
{
    Solution liuhao;
    int a = 0;
    cin >> a;

    system("pause"); // 添加这行代码让黑框停留
    return 0;
}