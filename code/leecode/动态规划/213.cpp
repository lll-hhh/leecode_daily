#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty())return 0;
        if(nums.size()==1)return nums[0];
        if(nums.size()==2)return max(nums[1],nums[0]);
        vector<int> nums2;
        for(int i=1;i<nums.size();i++)nums2.push_back(nums[i]);
        vector<int> dp1(nums.size()-1,0);
        vector<int> dp2(nums.size()-1,0);
        dp1[0]=nums[0];dp1[1]=max(nums[1],nums[0]);
        dp2[0]=nums2[0];dp2[1]=max(nums2[1],nums2[0]);
        for(int i=2;i<nums.size()-1;i++){
            dp1[i]=max(dp1[i-1],dp1[i-2]+nums[i]);
        }
        for(int i=2;i<nums2.size();i++){
            dp2[i]=max(dp2[i-1],dp2[i-2]+nums2[i]);
        }
        return max(dp1[nums2.size()-1],dp2[nums2.size()-1]);
    }
};
int main(){
    vector<int> lh={1,3,1,3};
    Solution s;
    cout<<s.rob(lh);
}