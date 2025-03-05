#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.empty())return 0;
        if(nums.size()==1)return 1;
        int maxsum=-1;
        int sum=1;
        for(int i=1;i<nums.size();i++){
            if(nums[i]-nums[i-1]>0){
                sum++;
                maxsum=max(sum,maxsum);
            }
            else {
                maxsum=max(sum,maxsum);
                sum=1;
            }
        }
        return maxsum;
    }
};