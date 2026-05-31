#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        if (word1.empty() && word2.empty())
            return 0;
        if (word1.empty())
            return word2.size();
        if (word2.empty())
            return word1.size();

        int w1 = word1.size();
        int w2 = word2.size();
        vector<vector<int>> dp(w1 + 1, vector<int>(w2 + 1, 0));

        int flag = 0;
        for (int i = 0; i < w2; i++)
        {
            if (word2[i] == word1[0])
            {
                flag = 1;
            }
            dp[0][i] = i + 1 - flag;
        }
        flag = 0;
        for (int i = 0; i < w1; i++)
        {
            if (word1[i] == word2[0])
            {
                flag = 1;
            }
            dp[i][0] = i + 1 - flag;
        }

        for (int i = 1; i < w1; i++)
        {
            for (int j = 1; j < w2; j++)
            {
                if (word1[i] == word2[j])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }

        return dp[w1 - 1][w2 - 1];
    }
};