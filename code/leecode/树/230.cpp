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
    int kthSmallest(TreeNode* root,int k) {
        stack<TreeNode*> stack1;
        int num=0;
        while(!stack1.empty()||root !=nullptr){
            while(root!=nullptr){
                stack1.push(root);
                root=root->left;
            }

            root=stack1.top();
            stack1.pop();

            num++;
            if(num==k)return root->val;
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