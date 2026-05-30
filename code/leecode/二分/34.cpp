#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftAns = -1;                                      // 记录 target 最左边的位置
        int rightAns = -1;                                     // 记录 target 最右边的位置

        int left = 0;                                          // 第一次二分的左边界
        int right = nums.size() - 1;                           // 第一次二分的右边界

        while (left <= right) {                                // 第一次二分：找最左边的 target
            int mid = left + (right - left) / 2;               // 计算中点

            if (nums[mid] == target) {                         // 如果找到 target
                leftAns = mid;                                 // 先记录当前位置
                right = mid - 1;                               // 继续往左找，看有没有更左的 target
            } else if (nums[mid] < target) {                   // 如果中点太小
                left = mid + 1;                                // 去右边找
            } else {                                           // 如果中点太大
                right = mid - 1;                               // 去左边找
            }
        }

        left = 0;                                               // 第二次二分重新初始化左边界
        right = nums.size() - 1;                                // 第二次二分重新初始化右边界

        while (left <= right) {                                 // 第二次二分：找最右边的 target
            int mid = left + (right - left) / 2;                // 计算中点

            if (nums[mid] == target) {                          // 如果找到 target
                rightAns = mid;                                 // 先记录当前位置
                left = mid + 1;                                 // 继续往右找，看有没有更右的 target
            } else if (nums[mid] < target) {                    // 如果中点太小
                left = mid + 1;                                 // 去右边找
            } else {                                            // 如果中点太大
                right = mid - 1;                                // 去左边找
            }
        }

        return {leftAns, rightAns};                             // 返回最左和最右位置
    }
};
class Solution1 {
public:
    int search(vector<int>& nums, int target) {             // 在有序数组 nums 中找 target
        int left = 0;                                       // 左边界，包含
        int right = nums.size() - 1;                        // 右边界，包含

        while (left <= right) {                             // 当区间还有元素时继续找
            int mid=left+(right-left)/2;
            if(nums[mid]==target){
                return mid;
            }else if(nums[mid]>target){
                left=mid+1;
            }else{
                right=mid-1;
            }
        }

        return -1;                                          // 没找到，返回 -1
    }
};