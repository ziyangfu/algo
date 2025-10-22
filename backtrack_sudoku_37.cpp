#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

// 给定一个部分填充的 9×9 数独网格,使得最终的网格满足数独的所有规则
// 每一行 都包含数字 1-9，且每个数字只能出现一次。
// 每一列 都包含数字 1到 9，且每个数字只能出现一次。
// 每一个 3×3的子网格（通常称为“宫”或“块”）都包含数字 1到 9，且每个数字只能出现一次。


class Solution {
private:
    /**
     * @brief 检查在 (row, col) 位置填充数字 val 是否合法
     * @param board 数独板
     * @param row 行索引
     * @param col 列索引
     * @param val 要填充的数字（字符 '1' 到 '9'）
     * @return 如果合法，返回 true
     */
    bool isValid(const std::vector<std::vector<char>>& board, int row, int col, char val) {
        // 1. 检查行
        for (int j = 0; j < 9; ++j) {
            if (board[row][j] == val) {
                return false;
            }
        }

        // 2. 检查列
        for (int i = 0; i < 9; ++i) {
            if (board[i][col] == val) {
                return false;
            }
        }

        // 3. 检查 3x3 九宫格
        // 计算九宫格的起始行和起始列
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; ++i) {
            for (int j = startCol; j < startCol + 3; ++j) {
                if (board[i][j] == val) {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * @brief 回溯函数，尝试解数独
     * @param board 数独板（注意：传引用以便修改）
     * @return 如果找到一个解，返回 true
     */
    bool backtrack(std::vector<std::vector<char>>& board) {
        // 遍历整个板寻找第一个空白单元格
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                
                // 找到空白单元格
                if (board[i][j] == '.') {
                    
                    // 尝试填充数字 1 到 9
                    for (char val = '1'; val <= '9'; ++val) {
                        
                        if (isValid(board, i, j, val)) {
                            // 1. 选择：填入数字
                            board[i][j] = val;
                            
                            // 2. 递归：搜索下一个解。如果递归返回 true，说明找到解了
                            if (backtrack(board)) {
                                return true; // 成功找到解，层层返回 true
                            }
                            
                            // 3. 撤销选择（回溯）：如果 val 无法导致最终解，重置并尝试下一个 val
                            board[i][j] = '.'; 
                        }
                    }
                    
                    // 如果 1-9 都尝试完毕，没有找到有效的解，则返回 false，回溯到上一个单元格
                    return false;
                }
            }
        }
        
        // 终止条件：如果循环结束都没有找到 '.'，说明整个板已经填满
        return true; 
    }

public:
    void solveSudoku(std::vector<std::vector<char>>& board) {
        backtrack(board);
    }
};

// 示例程序：如何在 main 中使用

void printBoard(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << board[i][j] << (j == 8 ? "" : " ");
            if ((j + 1) % 3 == 0 && j != 8) {
                std::cout << "| ";
            }
        }
        std::cout << "\n";
        if ((i + 1) % 3 == 0 && i != 8) {
            std::cout << "------+-------+------\n";
        }
    }
}

int main() {
    std::vector<std::vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    std::cout << "--- 原始数独板 ---\n";
    printBoard(board);

    Solution solver;
    solver.solveSudoku(board);

    std::cout << "\n--- 解完的数独板 ---\n";
    printBoard(board);

    return 0;
}
