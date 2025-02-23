#include<bits/stdc++.h>
using namespace std;

// class Solution {
// public:
//     int minSubArrayLen(int target, vector<int>& nums) {
//         int min=10000000;
//         for(int i=0;i<nums.size();i++){
//             int num=0;
//             int val=0;
//             for(int j=i;j<nums.size();j++){
//                 val+=nums[j];
//                 num++;
//                 if(val>=target){
//                     if(num<min){
//                         min=num;
//                     }
//                     break;
//                 }
//             }
//         }
//         if(min==10000000){
//             return 0;
//         }
//         return min;
//     }
// };
class Solution{
public:
    int minSubArrayLen(int target, vector<int>& nums){
        int n=nums.size();
        int min=n+1;
        int sum=0;
        int left=0;
        for(int right=0;right<n;right++){
            sum+=nums[right];
            if(sum>=target){
                while(sum-nums[left]>=target){
                    sum-=nums[left];
                    left++;
                }
                if(min>right-left+1){
                    min=right-left+1;
                }
            }
        }
        if(min==n+1)return 0;
        return min;
    }
};

