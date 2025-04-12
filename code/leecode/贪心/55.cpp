#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.empty())return false;
        if(nums.size()==1)return true;
        int si=nums.size();
        int maxx=nums[0];
        if(maxx==0)return 0;
        for(int i=0;i<si;){
            for(int j=i+1;j<=maxx;j++){
                if(maxx<j+nums[j]){
                    i=j;
                    maxx=j+nums[j];
                }
                if(maxx>=si-1)return 1;
                if(j==maxx)return 0;
            }
        }    
        return 0;
    }
};

int main(){
    Solution solu;
    vector<int> lh{0,1};
    cout<<solu.canJump(lh);
}


