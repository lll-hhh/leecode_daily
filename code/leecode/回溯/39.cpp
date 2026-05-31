#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> path;
    vector<vector<int>> ans;
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        dfs(candidates,target,0);
        return ans;
    }
    void dfs(vector<int>& candidates,int target,int start){
        if(target==0){
            ans.push_back(path);
            return;
        }
        if(target<0)return;

        for(int i=start;i<candidates.size();i++){
            path.push_back(candidates[i]);
            dfs(candidates,target-candidates[i],i);
            path.pop_back();
        }

    }

};