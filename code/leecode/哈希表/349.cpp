#include<bits/stdc++.h>
using namespace std;
class Solution {
    public:
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
            vector<int> answer;
            if(nums1.empty()||nums2.empty())return answer;

            sort(nums1.begin(),nums1.end());
            sort(nums2.begin(),nums2.end());

            for(int i=0,j=0;i<nums1.size() && j<nums2.size();){
               
                if(nums1[i]==nums2[j]){
                    
                    answer.push_back(nums1[i]);
                    int temp=nums1[i];

                    while(i<nums1.size() && nums1[i]==temp )i++;
                    while(j<nums2.size() && nums2[j]==temp )j++;
                }
                else if(nums1[i]>nums2[j])j++;
                else i++;
            }
            return answer;
        }
    };
int main(){
    vector<int> a={4,4};
    vector<int> b={7,6,6,23};
    Solution sulo;
    vector c=sulo.intersection(a,b);
    for(auto& a:c)cout<<a<<' ';
    cout<<endl;
}