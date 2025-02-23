#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        vector<vector<int>> generateMatrix(int n) {
            vector<vector<int>> ans(n,vector<int>(n));
            int left=0,right=n-1,low=n-1,up=0;
            int num=1;
            while(num<=n*n){
                for(int i=left;i<=right;i++){
                    ans[up][i]=num;
                    num++;
                }
                up++;
                for(int i=up;i<=low;i++){
                    ans[i][right]=num;
                    num++;
                }
                right--;
                for(int i=right;i>=left;i--){
                    ans[low][i]=num;
                    num++;
                }
                low--;
                for(int i=low;i>=up;i--){
                    ans[i][left]=num;
                    num++;
                }
                left++;
            }
            return ans;
        }
};