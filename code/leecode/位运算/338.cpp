#include <bits/stdc++.h>
using namespace std;

class Solution
{

public:
    vector<int> countBits(int n)
    {
        vector<int> answer;
        for (int i = 0; i <= n; i++)
        {
            int jishu = 0;
            int ii = i;
            while (ii)
            {
                jishu += ii & 1;
                ii >>= 1;
            }
            answer.push_back(jishu);
        }
        return answer;
    }
};

int main()
{
    Solution liuhao;
    int a = 0;
    cin >> a;
    for (auto c : liuhao.countBits(a))
    {
        cout << c << endl;
    }
    system("pause"); // 添加这行代码让黑框停留
    return 0;
}