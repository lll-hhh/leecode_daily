#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            vector<vector<int>> answer;
            if(nums.empty())return answer;
            sort(nums.begin(),nums.end());
            for(int i=0;i<nums.size();i++){
                int thi=nums.size()-1;
                int sec=i+1;
                if (i > 0 && nums[i] == nums[i - 1]) {
                    continue;
                }
                for(;thi>=sec;){
                    if(thi<nums.size()-1&&nums[thi]==nums[thi+1]){
                        thi--;
                    }
                    else if(sec>i+1&&nums[sec]==nums[sec-1]){
                        sec++;
                    }
                    else {
                        if(nums[i]+nums[sec]+nums[thi]==0){
                            if(i!=thi&&sec!=thi&&i!=sec){
                            answer.push_back(vector<int>{nums[sec],nums[i],nums[thi]});
                            }
                            sec++;
                        }
                        else if(nums[i]+nums[sec]+nums[thi]>0){
                            thi--;
                        }
                        else sec++;
                    }
                }
            }
            return answer;
        }
};
int main(){
    Solution sulo;
    vector<int> nums={1,0,-1,0,0,-2,2};
    vector<vector<int>> a=sulo.threeSum(nums);
    for(auto& x:a){
        for(auto& y:x){
            cout<<y<<' ';
        }
        cout<<endl;
    }
    return 0;
}