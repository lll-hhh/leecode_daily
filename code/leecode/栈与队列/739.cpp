
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    stack<pair<int, int>> liuhao;
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        if (temperatures.empty())
            return {};
        vector<int> answer(temperatures.size(), 0);
        liuhao.push(pair<int, int>(temperatures[0], 0));
        for (int i = 1; i < temperatures.size(); i++)
        {
            while (!liuhao.empty() && temperatures[i] > liuhao.top().first)
            {
                answer[liuhao.top().second] += i - liuhao.top().second;
                liuhao.pop();
            }
            liuhao.push(pair<int, int>(temperatures[i], i));
        }
        return answer;
    }
};