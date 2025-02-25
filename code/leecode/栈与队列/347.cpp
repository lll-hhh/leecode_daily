#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool comp(array<int, 2> a,array<int, 2> b){
        return a[1]>b[1];
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<array<int, 2>> lh(nums.size(),{0,0});
        for(auto& a:nums){
            for(auto& b:lh){
                if(b[0]==a){
                    b[1]++;
                }
                if(b[1]==0){
                    b[0]=a;
                    b[1]++;
                }
            }
        }
        sort(lh.begin(),lh.end(),[](array<int, 2> a,array<int, 2> b){
            return a[1]>b[1];});
        vector<int> answer;
        for(int i=0;i<k;i++){
            answer.push_back(lh[i][0]);
        }
    }

};

class Solution{
public:
    vector<int> top(vector<int>& nums,int k){
        unordered_map<int,int> fremap;
        for(auto& a:nums){
            fremap[a]++;
        }

        vector<array<int,2>> lh;
        for(const auto& a:fremap){
            lh.push_back({a.first,a.second});
        }
        sort(lh.begin(),lh.end(),[](array<int,2>& a,array<int,2>& b){
            return a[1]>b[1];
        });
        vector<int> lc;
        for(int i=0;i<k;i++){
            lc.push_back(lh[i][0]);
        }
        return lc;
    }
};




class Solution {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k) {
            // 使用哈希表统计每个数字的频率
            unordered_map<int, int> freqMap;
            for (auto& num : nums) {
                freqMap[num]++;
            }
    
            // 将频率信息存储到数组中
            vector<array<int, 2>> freqArray;
            for (const auto& entry : freqMap) {
                freqArray.push_back({entry.first, entry.second});
            }
    
            // 按照频率降序排序
            sort(freqArray.begin(), freqArray.end(), [](const array<int, 2>& a, const array<int, 2>& b) {
                return a[1] > b[1]; // 按频率降序排序
            });
    
            // 提取前 k 个高频元素
            vector<int> result;
            for (int i = 0; i < k && i < freqArray.size(); ++i) {
                result.push_back(freqArray[i][0]); // 取数组的第一个元素（数值）
            }
    
            return result;
        }
    };
    
int main(){
    Solution solu;
    vector<int> lh{1,1,1,2,2,3};
    for(auto& a:solu.topKFrequent(lh,2))cout<<a<<' ';
}