
#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    int nums2[100005];

public:
    vector<int> findDisappearedNumbers(vector<int> &nums)
    {
        vector<int> answer;
        for (auto a : nums)
        {
            nums2[a] = 1;
        }
        for (int i = 1; i <= nums.size(); i++)
        {
            if (!nums2[i])
                answer.push_back(i);
        }
        return answer;
    }
};
int main()
{
    Solution liuhao;
    int a = 0;
    cin >> a;

    system("pause"); // 添加这行代码让黑框停留
    return 0;
}