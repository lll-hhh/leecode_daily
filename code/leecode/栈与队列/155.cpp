#include <bits/stdc++.h>
using namespace std;
class MinStack
{
public:
    stack<pair<int, int>> liuhao;
    MinStack()
    {
        liuhao;
    }

    void push(int val)
    {
        if (liuhao.empty())
        {
            liuhao.push({val, val});
        }
        else
            liuhao.push(pair<int, int>(val, min(val, liuhao.top().second)));
    }

    void pop()
    {
        liuhao.pop();
    }

    int top()
    {
        return liuhao.top().first;
    }

    int getMin()
    {
        return liuhao.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */