#include<bits/stdc++.h>
class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        if(nums.size()==0){
            return 0;
        }
        int i=0;
        int j=nums.size()-1;
        while(i<j){
            int ii=i;
            for(;ii<j&&nums[ii]!=val;ii++);
            i=ii;
            int jj=j;
            for(;jj>i&&nums[jj]==val;jj--);
            j=jj;
            std::swap(nums[i],nums[j]);
        }
        int k=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]!=val)k++;
        }
        return k;
    }
};
int main(){
    Solution s;
    std::vector<int> nums={0,1,2,2,3,0,4,2};
    int val=2;
    std::cout<<s.removeElement(nums,val)<<std::endl;
    return 0;
}
