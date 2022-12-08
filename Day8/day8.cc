#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<string> vs;

bool visible(const vs& grid, vs::size_type y, string::size_type x)
{
    // Up
    bool visible = true;
    for (vs::size_type i = 0; i < y; i++) {
        if (grid[i][x] >= grid[y][x]) {
            visible = false;
            break;
        }
    }
    if (visible) return true;

    // Down
    visible = true;
    for (vs::size_type i = y + 1; i < grid.size(); i++) {
        if (grid[i][x] >= grid[y][x]) {
            visible = false;
            break;
        }
    }
    if (visible) return true;

    // Left
    visible = true;
    for (string::size_type i = 0; i < x; i++) {
        if (grid[y][i] >= grid[y][x]) {
            visible = false;
            break;
        }
    }
    if (visible) return true;

    // Right
    visible = true;
    for (string::size_type i = x + 1; i < grid[y].size(); i++) {
        if (grid[y][i] >= grid[y][x]) {
            visible = false;
            break;
        }
    }
    if (visible) return true;

    return false;
}

int scenic_score(vs& grid, vs::size_type y, string::size_type x)
{
    int up = 0;
    for (vs::difference_type i = y - 1; i >= 0; i--) {
        up++;
        if (grid[i][x] >= grid[y][x]) {
            break;
        }
    }

    int down = 0;
    for (vs::size_type i = y + 1; i < grid.size(); i++) {
        down++;
        if (grid[i][x] >= grid[y][x]) {
            break;
        }
    }
    
    int left = 0;
    for (string::difference_type i = x - 1; i >= 0; i--) {
        left++;
        if (grid[y][i] >= grid[y][x]) {
            break;
        }
    }

    int right = 0;
    for (string::size_type i = x + 1; i < grid[y].size(); i++) {
        right++;
        if (grid[y][i] >= grid[y][x]) {
            break;
        }
    }
    return up * down * left * right;
}

int main()
{
    ifstream is("day8.txt");
    vs heights;
    string line;
    while (is >> line) {
        heights.push_back(line);
    }
    is.close();

    auto count = 2 * heights.size() + 2 * heights[0].size() - 4; // Edges
    int score = INT_MIN;
    for (vs::size_type i = 1; i < heights.size() - 1; i++) {
        for (string::size_type j = 1; j < heights[i].size() - 1; j++) {
            if (visible(heights, i, j)) {
                count++;
            }
            score = max(score, scenic_score(heights, i, j));
        }
    }

    cout << count << endl; // Part 1
    cout << score << endl; // Part 2

    return 0;
}

