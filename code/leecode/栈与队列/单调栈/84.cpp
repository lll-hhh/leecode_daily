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
class Solution {                                                        // 定义解题类
public:                                                                // 公共成员，LeetCode 会调用这里的函数

    int largestRectangleArea(vector<int>& heights) {                   // 主函数：返回柱状图中最大的矩形面积
        
        heights.insert(heights.begin(), 0);                            // 在最左边加一个高度为 0 的哨兵，防止栈空

        heights.push_back(0);                                          // 在最右边加一个高度为 0 的哨兵，用来清空栈

        stack<int> st;                                                  // 单调栈，里面存柱子的下标

        int ans = 0;                                                    // ans 记录最大矩形面积

        for(int i=0;i<heights.size();i++){
            while(!st.empty()&&heights[i]<heights[st.top()]){
                int h=heights[st.top()];
                st.pop();
                int weight=i-st.top()-1;
                int mianji=weight*h;
                ans=max(ans,mianji);
            }
            st.push(i);
        }
        return ans;                                                    // 返回最大矩形面积
    }                                                                  // largestRectangleArea 函数结束
};                                                                      // Solution 类结束
int main(){
    Solution sulo;
    vector<int>lc{2,1,5,6,2,3};
    cout<<sulo.largestRectangleArea(lc);
}