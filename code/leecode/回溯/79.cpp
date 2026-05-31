#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int m, n;
    vector<vector<bool>> used;

    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size();
        n = board[0].size();
        used.assign(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dfs(board, word, i, j, 0))
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool dfs(vector<vector<char>> &board, string &word, int i, int j, int k)
    {
        if (board[i][j] != word[k])
        {
            return false;
        }

        if (k == word.size() - 1)
        {
            return true;
        }

        used[i][j] = true;

        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};

        for (int d = 0; d < 4; d++)
        {
            int x = i + dx[d];
            int y = j + dy[d];

            if (x < 0 || x >= m || y < 0 || y >= n)
            {
                continue;
            }

            if (used[x][y])
            {
                continue;
            }

            if (dfs(board, word, x, y, k + 1))
            {
                return true;
            }
        }

        used[i][j] = false;
        return false;
    }
};