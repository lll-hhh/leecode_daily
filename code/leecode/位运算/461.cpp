#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int hammingDistance(int x, int y)
    {
        int s = x ^ y;
        int answer = 0;
        while (s)
        {
            answer += s & 1;
            s >>= 1;
        }
        return answer;
    }
};
int main()
{
    Solution liuhao;
    int a, b;
    cin >> a >> b;
    cout << liuhao.hammingDistance(a, b);
    system("pause"); // 添加这行代码让黑框停留
    return 0;
}