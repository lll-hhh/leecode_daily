#include <bits/stdc++.h>
using namespace std;
class Solution
{       // LeetCode 固定写法：定义一个 Solution 类
public: // public 表示下面的函数可以被 LeetCode 调用
    double findMedianSortedArrays(vector<int> &a, vector<int> &b)
    { // 函数：传入两个升序数组，返回中位数
        if (a.size() > b.size())
        {
            return findMedianSortedArrays(b, a);
        }

        int amax = a.size();
        int bmax = b.size();
        int ah = a.size();
        int al = 0;

        int zonghena = (a.size() + b.size() + 1) / 2;

        int leftA, leftB, rightA, rightB;
        while (1)
        {
            int takeA = al + (ah - al) / 2;
            int takeB = zonghena - takeA;
            if (takeA == 0)
                leftA = INT_MIN;
            else
                leftA = a[takeA - 1];

            if (takeA == amax)
                rightA = INT_MAX;
            else
                rightA = a[takeA];

            if (takeB == 0)
                leftB = INT_MIN;
            else
                leftB = b[takeB - 1];

            if (takeB == bmax)
                rightB = INT_MAX;
            else
                rightB = b[takeB];

            if (leftA <= rightB && leftB <= rightA)
            {
                if ((a.size() + b.size()) % 2 == 1)
                    return max(leftA, leftB);
                else
                {
                    int leftMax = max(leftA, leftB);    // 找出左半边最大的数
                    int rightMin = min(rightA, rightB); // 找出右半边最小的数
                    return (leftMax + rightMin) / 2.0;  // 中位数就是这两个数的平均值
                }
            }
            else if (leftA > rightB)
                ah = takeA - 1;
            else
                al = takeA + 1;
        }
        return 0.0; // 理论上不会走到这里，只是为了让函数一定有返回值
    } // while 结束
}; // 类结束