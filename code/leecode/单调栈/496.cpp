#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> answer;
        if(nums1.empty()||nums2.empty())return answer;
        lenth=0;
        lh=vector<int>(nums2.size(),0);
        vector<int> lc(nums2.size(),-1);

        for(int i=0;i<nums2.size();i++){

            if(empty()||nums2[i]<nums2[getop()]){
                push(i);
            }
            else if(nums2[i]>nums2[getop()]){
                int temp=pop();
                lc[temp]=nums2[i];
                while(1){
                    if(empty()||nums2[i]<nums2[getop()]){
                        push(i);
                        break;
                    }
                    temp=pop();
                    lc[temp]=nums2[i];
                }
            }
        }
        for(auto& a:nums1){
            for(int i=0;i<nums2.size();i++){
                if(a==nums2[i]){
                    answer.push_back(lc[i]);
                }
            }
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
    vector<int> b{75,71};
    vector<int> a{73,74,75,71,69,72,76};
    vector<int> e=solu.nextGreaterElement(b,a);
    for(auto& c:e)cout<<c<<' ';
}