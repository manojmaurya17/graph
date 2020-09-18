#include <iostream>
#include <vector>
using namespace std;

// leetcode 200
void dfs(int x, int y, vector<vector<char>> &grid)
{
    grid[x][y] = '0';
    int dir[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < 4; i++)
    {
        int r = x + dir[i][0];
        int c = y + dir[i][1];
        if (r >= 0 && c >= 0 && r < grid.size() && c < grid[0].size() && grid[r][c] != '0')
        {
            dfs(r, c, grid);
        }
    }
}

int numIslands(vector<vector<char>> &grid)
{
    int counts = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            if (grid[i][j] == '1')
            {
                dfs(i, j, grid);
                counts++;
            }
        }
    }
    return counts;
}