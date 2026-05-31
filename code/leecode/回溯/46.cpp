# include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> used;
    vector<int> path;

    vector<vector<int>> permute(vector<int>& nums) {
        used.resize(nums.size(),0);

        backward(nums);

        return ans;
    }

    void backward(vector<int>& nums){
        if(path.size()==used.size()){
            ans.push_back(path);
            return;
        }
        for(int i=0;i<used.size();i++){
            if(used[i]==1)continue;

            path.push_back(nums[i]);
            used[i]=1;

            backward(nums);

            used[i]=0;
            path.pop_back();
        }
    }


};