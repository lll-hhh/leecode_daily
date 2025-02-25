#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<int> nextGreaterElements(vector<int>& nums) {
            vector<int> answer;
            if(nums.empty()||nums.empty())return answer;

            int maxn=-100;
            int index;
            for(int i=0;i<nums.size();i++){
                if(maxn<nums[i]){
                    maxn=nums[i];
                    index=i;
                }
            }
            index++;
            vector<int> nums3;
            for(int i=index;i<nums.size();i++){
                nums3.push_back(nums[i]);
            }
            for(int i=0;i<index;i++){
                nums3.push_back(nums[i]);
            }


            lenth=0;
            lh=vector<int>(nums.size(),0);
            vector<int> lc(nums.size(),-1);
    
            for(int i=0;i<nums3.size();i++){
    
                if(empty()||nums3[i]<=nums3[getop()]){
                    push(i);
                }
                else if(nums3[i]>nums3[getop()]){
                    int temp=pop();
                    lc[temp]=nums3[i];
                    while(1){
                        if(empty()||nums3[i]<=nums3[getop()]){
                            push(i);
                            break;
                        }
                        temp=pop();
                        lc[temp]=nums3[i];
                    }
                }
            }
            index=nums.size()-index+1;
            for(int i=index-1;i<lc.size();i++){
                answer.push_back(lc[i]);
            }
            for(int i=0;i<index-1;i++){
                answer.push_back(lc[i]);
            }

            return answer;
        }
    private:
        int lenth;
        vector<int> lh;
        int pop(){
            return lh[--lenth];
        }
        void push(int x){
            lh[lenth++]=x;
        }
        int getop(){
            return lh[lenth-1];
        }
        bool empty(){
            return lenth==0;
        }
    };
int main(){
    Solution solu;
    vector<int> lh{1,2,3,4,3};
    for(auto& a:solu.nextGreaterElements(lh))cout<<a<<endl;

}