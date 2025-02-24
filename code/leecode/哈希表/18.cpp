#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        vector<vector<int>> fourSum(vector<int>& nums, int target) {
            vector<vector<int>> answer;
            if(nums.size()<4)return answer;
            long long target1=target;
            sort(nums.begin(),nums.end());
            for(int i=0;i<nums.size()-3;i++){
                if(i>0&&nums[i]==nums[i-1])continue;
                for(int j=i+1;j<nums.size()-2;j++){
                    if(j>i+1&&nums[j]==nums[j-1])continue;
                    long long c=j+1;
                    long long d=nums.size()-1;
                    while(c<d){
                        long long s=nums[i]+nums[j]+(long long)nums[c]+(long long)nums[d];
                        if(s==target1){
                            answer.push_back(vector<int>{nums[i],nums[j],nums[c],nums[d]});
                            for (c++; c < d && nums[c] == nums[c - 1]; c++); 
                            for (d--; d > c && nums[d] == nums[d + 1]; d--); 
                        }
                        else if(s<target){
                            c++;
                        }
                        else if(s>target){
                            d--;
                        }
                    }
                }
            }
            return answer;
        }
};
int main(){
    Solution sulo;
    vector<int> nums={1000000000,1000000000,1000000000,1000000000};
    vector<vector<int>> a=sulo.fourSum(nums,4000000000);
    for(auto& x:a){
        for(auto& y:x){
            cout<<y<<' ';
        }
        cout<<endl;
    }
    return 0;
}