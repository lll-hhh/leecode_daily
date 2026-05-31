#include <bits/stdc++.h> // 引入 C++ 常用头文件
using namespace std; // 使用标准命名空间

class Solution { // 定义 Solution 类
public: // LeetCode 要求函数是 public

    vector<vector<string>> ans; // 保存所有合法棋盘
    vector<string> board; // 保存当前正在尝试的棋盘

    vector<vector<string>> solveNQueens(int n) { // 主函数，输入棋盘大小 n
        board = vector<string>(n, string(n, '.')); // 创建 n 行 n 列的棋盘，初始全是 '.'
        dfs(0, n); // 从第 0 行开始放皇后
        return ans; // 返回所有答案
    } // solveNQueens 函数结束

    void dfs(int row, int n) { // 回溯函数，row 表示当前要放第几行
        if (row == n) { // 如果 row == n，说明第 0 到 n-1 行都放好了
            ans.push_back(board); // 当前棋盘是一个合法方案，加入答案
            return; // 返回上一层，继续找别的方案
        } // if 结束

        for (int col = 0; col < n; col++) { // 枚举当前 row 行的每一列
            if (!isValid(row, col, n)) { // 如果当前位置不能放皇后
                continue; // 跳过这一列，试下一列
            } // if 结束

            board[row][col] = 'Q'; // 在当前位置放一个皇后
            dfs(row + 1, n); // 继续去下一行放皇后
            board[row][col] = '.'; // 回溯，撤销刚才放的皇后
        } // for 循环结束
    } // dfs 函数结束

    bool isValid(int row, int col, int n) { // 判断 board[row][col] 能不能放皇后
        for (int i = 0; i < row; i++) { // 检查当前列的上方有没有皇后
            if (board[i][col] == 'Q') { // 如果同一列上方已经有皇后
                return false; // 当前位置不能放
            } // if 结束
        } // for 结束

        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { // 检查左上斜线
            if (board[i][j] == 'Q') { // 如果左上斜线有皇后
                return false; // 当前位置不能放
            } // if 结束
        } // for 结束

        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) { // 检查右上斜线
            if (board[i][j] == 'Q') { // 如果右上斜线有皇后
                return false; // 当前位置不能放
            } // if 结束
        } // for 结束

        return true; // 列、左上、右上都没冲突，可以放皇后
    } // isValid 函数结束
}; // Solution 类结束