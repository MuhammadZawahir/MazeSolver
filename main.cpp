#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

// Maze dimensions
const int rows = 10;
const int cols = 10;

// Directions for movement (up, down, left, right)
const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Function to print the maze
void printMaze(const vector<vector<char>> &maze)
{
    for (const auto &row : maze)
    {
        for (char cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// BFS to find the shortest path
bool bfs(pair<int, int> start, pair<int, int> end, vector<vector<char>> &maze)
{
    set<pair<int, int>> visited;
    queue<pair<pair<int, int>, vector<pair<int, int>>>> q;

    visited.insert(start);
    q.push({start, {start}});

    vector<vector<pair<int, int>>> paths;

    while (!q.empty())
    {
        pair<pair<int, int>, vector<pair<int, int>>> front = q.front();
        q.pop();

        pair<int, int> curr = front.first;          // current position
        vector<pair<int, int>> path = front.second; // path so far

        if (curr == end)
        {
            paths.push_back(path);
        }
        else
        {
            int i = curr.first, j = curr.second;

            for (auto &direction : directions)
            {
                int new_i = i + direction[0];
                int new_j = j + direction[1];

                if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols &&
                    visited.find({new_i, new_j}) == visited.end() && maze[new_i][new_j] == ' ')
                {
                    visited.insert({new_i, new_j});
                    vector<pair<int, int>> new_path = path;
                    new_path.push_back({new_i, new_j});
                    q.push({{new_i, new_j}, new_path});
                }
            }
        }
    }

    if (paths.empty())
    {
        return false;
    }

    // Find the shortest path
    vector<pair<int, int>> min_path = paths[0];
    for (const auto &path : paths)
    {
        if (path.size() < min_path.size())
        {
            min_path = path;
        }
    }

    // Mark the shortest path on the maze
    for (const auto &p : min_path)
    {
        maze[p.first][p.second] = 'X';
    }

    return true;
}

int main()
{
    vector<vector<char>> maze = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', ' ', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

    pair<int, int> start = {1, 1};
    pair<int, int> end = {9, 8};

    if (bfs(start, end, maze))
    {
        printMaze(maze);
    }
    else
    {
        cout << "No path found!" << endl;
    }

    return 0;
}
