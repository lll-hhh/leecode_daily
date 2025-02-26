#include<bits/stdc++.h>
using namespace std;
// class Solution {
//     public:
//         int largestRectangleArea(vector<int>& heights) {
//             if(heights.empty())return 0;
//             int max=-1;
//             for(int i=0;i<heights.size();i++){
//                 int j=i+1;
//                 int k=i-1;
//                 while(j<heights.size()&&heights[j]>=heights[i])j++;
//                 while(k>=0&&heights[k]>=heights[i])k--;
//                 int s=(j-k-1)*heights[i];
//                 max=max>s?max:s;
//             }
//             return max;
//         }
//     };
class Solution {
    public:
        int largestRectangleArea(vector<int>& heights) {
            if (heights.empty()) return 0;
    
            int n = heights.size();
            vector<int> left(n);  // 记录每个柱子左侧最近的小于它的柱子的索引
            vector<int> right(n, n); // 记录每个柱子右侧最近的小于它的柱子的索引，默认为 n
    
            // 计算 left 数组
            stack<int> mono_stack;
            for (int i = 0; i < n; ++i) {
                while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                    mono_stack.pop();
                }
                left[i] = mono_stack.empty() ? -1 : mono_stack.top();
                mono_stack.push(i);
            }
    
            // 清空栈，重新用于计算 right 数组
            while (!mono_stack.empty()) mono_stack.pop();
    
            // 计算 right 数组
            for (int i = n - 1; i >= 0; --i) {
                while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                    mono_stack.pop();
                }
                right[i] = mono_stack.empty() ? n : mono_stack.top();
                mono_stack.push(i);
            }
    
            // 计算最大面积
            int max_area = 0;
            for (int i = 0; i < n; ++i) {
                max_area = max(max_area, (right[i] - left[i] - 1) * heights[i]);
            }
    
            return max_area;
        }
    };
int main(){
    Solution sulo;
    vector<int>lc{2,1,5,6,2,3};
    cout<<sulo.largestRectangleArea(lc);
}