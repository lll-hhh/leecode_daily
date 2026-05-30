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
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stack1;
        long long inorder=(long long)INT_MIN-1;

        while(!stack1.empty()||root !=nullptr){
            while(root!=nullptr){
                stack1.push(root);
                root=root->left;
            }

            root=stack1.top();
            stack1.pop();

            if(inorder>=root->val)return false;
            inorder=root->val;
            root=root->right;
        }
        return true;
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