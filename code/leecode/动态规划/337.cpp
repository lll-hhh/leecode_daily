#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    unordered_map <TreeNode*, int> f, g;
    int rob(TreeNode* root) {
        maxrob(root);
        return max(f[root],g[root]);
    }
    void maxrob(TreeNode* root){
       if(!root)return;
       maxrob(root->right);
       maxrob(root->left);
       f[root]=root->val+g[root->left]+g[root->right];
       g[root]=max(f[root->left],g[root->left])+max(f[root->right],g[root->right]);
    }
};