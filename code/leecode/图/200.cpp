#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    void xuanran(vector<vector<char>> &grid, int i, int j)
    {
        queue<pair<int, int>> liuhao;
        liuhao.push(pair<int, int>(i, j));
        grid[i][j] = '2';
        while (!liuhao.empty())
        {
            pair<int, int> node = liuhao.front();
            liuhao.pop();
            if (node.first && grid[node.first - 1][node.second] == '1')
            {
                liuhao.push(pair<int, int>(node.first - 1, node.second));
                grid[node.first - 1][node.second] = '2';
            }
            if (node.second && grid[node.first][node.second - 1] == '1')
            {
                liuhao.push(pair<int, int>(node.first, node.second - 1));
                grid[node.first][node.second - 1] = '2';
            }
            if (node.first < grid.size() - 1 && grid[node.first + 1][node.second] == '1')
            {
                liuhao.push(pair<int, int>(node.first + 1, node.second));
                grid[node.first + 1][node.second] = '2';
            }
            if (node.second < grid[0].size() - 1 && grid[node.first][node.second + 1] == '1')
            {
                liuhao.push(pair<int, int>(node.first, node.second + 1));
                grid[node.first][node.second + 1] = '2';
            }
        }
    }
    int numIslands(vector<vector<char>> &grid)
    {
        int ans = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == '1')
                {
                    ans++;
                    xuanran(grid, i, j);
                }
            }
        }
        return ans;
    }
};
int main()
{
}