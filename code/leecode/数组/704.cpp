#include<bits/stdc++.h>
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int lower=0;
        int upper=nums.size()-1;

        while(lower<=upper){
            int mid=lower+(upper-lower)/2;
            if(nums[mid]==target){
                return mid;
            }
            else if(nums[mid]<target){
                lower=mid+1;
            }
            else if(nums[mid]>target){
                upper=mid-1;
            }
        }
        return -1;
    }
};
int main(){
    Solution s;
    std::vector<int> nums={-1,0,3,5,9,12};
    int target=9;
    std::cout<<s.search(nums,target)<<std::endl;
    return 0;
}