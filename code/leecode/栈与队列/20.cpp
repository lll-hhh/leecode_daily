
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> st;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '{' || s[i] == '[' || s[i] == '(')st.push(s[i]);
            else{
                if (st.empty()) return false;
                if (s[i] == ')')
                {
                    if (st.top() != '(')
                        return false;
                }
                else if (s[i] == '}')
                {
                    if (st.top() != '{')
                        return false;
                }
                else if (s[i] == ']')
                {
                    if (st.top() != '[')
                        return false;
                }
                            st.pop();
            }

        }
        return st.empty();
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