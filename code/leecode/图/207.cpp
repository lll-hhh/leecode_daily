#include <bits/stdc++.h>
using namespace std;
class Solution
{       // 定义解题类
public: // 公共成员，LeetCode 会调用这里的函数
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    { // 判断是否可以完成所有课程

        vector<vector<int>> qian(numCourses); // qian[x] 表示学完 x 后，可以继续学哪些课

        vector<int> hou(numCourses, 0); // hou[i] 表示课程 i 还有多少门前置课没学

        for (int i = 0; i < prerequisites.size(); i++) // 遍历所有先修关系，不是遍历 numCourses
        {                                              // for 开始
            int qian1 = prerequisites[i][0];           // qian1 表示想要学习的课程 ai

            int hou1 = prerequisites[i][1]; // hou1 表示 ai 的先修课程 bi

            qian[hou1].push_back(qian1); // 学完 hou1 后，才能学 qian1，所以建边 hou1 -> qian1

            hou[qian1]++; // qian1 多了一个前置课程，所以入度加一
        } // for 结束

        int le = 0; // le 表示已经学完的课程数量

        queue<int> liuhao; // 队列存放当前可以学习的课程

        for (int i = 0; i < numCourses; i++) // 遍历所有课程
        {                                    // for 开始
            if (hou[i] == 0)                 // 如果课程 i 没有前置课程
                liuhao.push(i);              // 课程 i 可以先学，放入队列
        } // for 结束

        while (!liuhao.empty())       // 只要还有可以学习的课程
        {                             // while 开始
            int now = liuhao.front(); // 取出当前可以学习的课程

            liuhao.pop(); // 弹出队首

            le++; // 学完一门课

            for (int i = 0; i < qian[now].size(); i++) // 遍历学完 now 后可以学习的课程
            {                                          // for 开始
                int next = qian[now][i];               // next 是真正的后续课程编号

                hou[next]--; // next 少了一门前置课程

                if (hou[next] == 0)
                    liuhao.push(next); // 如果 next 的前置课程都学完了，就入队
            } // for 结束
        } // while 结束

        if (le == numCourses) // 如果学完数量等于总课程数
            return true;      // 可以完成所有课程

        return false; // 否则说明有环，不能完成
    } // canFinish 函数结束
}; // Solution 类结束