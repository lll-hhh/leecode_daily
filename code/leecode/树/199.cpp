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
    queue<TreeNode*> liuhao;
    vector<int> rightSideView(TreeNode* root) {
        if(root==nullptr)return {};
        liuhao.push(root);
        vector<int> answer;
        answer.push_back(root->val);
        while(!liuhao.empty()){
            int k=liuhao.size();
            for(int i=0;i<k;i++){
                TreeNode* node=liuhao.front();
                liuhao.pop();
                if(node->left!=nullptr){
                    liuhao.push(node->left);
                }
                if(node->right!=nullptr){
                    liuhao.push(node->right);
                }
            }
            answer.push_back(liuhao.back()->val);
        }
        answer.pop_back();
        return answer;
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