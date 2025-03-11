#include <iostream>
#include <string>
using namespace std;

// ANSI color codes for coloring output in the terminal
#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"

// Define the maze as a 2D array, where 1 represents walls and 0 represents open paths.
// The maze is 15x15 and we have a start and end point defined below.
int maze[15][15] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Define starting and ending coordinates in the maze
// startX, startY is the start location
// endX, endY is the goal location
int startX = 13, startY = 0;
int endX = 1, endY = 14;

// Step counters to measure how many steps DFS and BFS take
int dfsSteps = 0, bfsSteps = 0;

// Visited arrays to keep track of visited positions for each search
bool visitedDFS[15][15];
bool visitedBFS[15][15];

// Depth First Search (DFS) recursive function
bool dfs(int x, int y) {
    // Check bounds, wall presence, or if already visited
    if (x < 0 || y < 0 || x >= 15 || y >= 15 || maze[x][y] == 1 || visitedDFS[x][y])
        return false;

    // Increment DFS steps
    dfsSteps++;

    // If we reached the end point, return true
    if (x == endX && y == endY)
        return true;

    // Mark this cell as visited
    visitedDFS[x][y] = true;

    // Try moving in all four directions (right, left, down, up)
    // If any direction leads to a solution, return true
    return dfs(x, y + 1) || dfs(x, y - 1) || dfs(x + 1, y) || dfs(x - 1, y);
}

// Breadth First Search (BFS) function
bool bfs() {
    // We will use a simple queue implemented with a 2D array
    // q will store positions (x, y)
    int q[225][2];
    int front = 0, rear = 0;

    // Initialize visitedBFS to false
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            visitedBFS[i][j] = false;

    // Enqueue the start position and mark it visited
    q[rear][0] = startX;
    q[rear][1] = startY;
    rear++;
    visitedBFS[startX][startY] = true;

    // Possible movements: right, left, down, up
    int directions[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

    // BFS loop
    while (front < rear) {
        // Dequeue the next position
        int x = q[front][0];
        int y = q[front][1];
        front++;

        // Increment BFS steps
        bfsSteps++;

        // Check if we reached the end
        if (x == endX && y == endY)
            return true;

        // Explore neighbors in all four directions
        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];

            // Check boundaries, walls, and visited status
            if (newX >= 0 && newY >= 0 && newX < 15 && newY < 15
                && maze[newX][newY] != 1 && !visitedBFS[newX][newY]) {
                // Enqueue the neighbor and mark as visited
                q[rear][0] = newX;
                q[rear][1] = newY;
                rear++;
                visitedBFS[newX][newY] = true;
            }
        }
    }
    // If we exhaust all possibilities and never reach the end, return false
    return false;
}

int main() {
    // Initialize the visited arrays for DFS
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            visitedDFS[i][j] = false;

    // Run DFS and BFS on the maze
    bool dfsResult = dfs(startX, startY);
    bool bfsResult = bfs();

    // Print results of searches
    cout << "\nResults:\n";
    cout << "DFS steps: " << dfsSteps << "\n";
    cout << "BFS steps: " << bfsSteps << "\n";

    if (dfsResult && bfsResult)
        cout << "Both DFS and BFS found the path.\n";
    else if (dfsResult)
        cout << "Only DFS found the path.\n";
    else if (bfsResult)
        cout << "Only BFS found the path.\n";
    else
        cout << "No path found by either DFS or BFS.\n";

    // Print legend for visualization
    cout << "\nLegend:\n";
    cout << "# = Wall\n";
    cout << ". = Unvisited Path (" << COLOR_YELLOW << "yellow" << COLOR_RESET << ")\n";
    cout << "D = DFS Visited\n";
    cout << "B = BFS Visited (" << COLOR_GREEN << "green" << COLOR_RESET << ")\n";
    cout << "S = Start\n";
    cout << "E = End\n\n";

    // Print the maze with DFS visited nodes highlighted
    cout << "Maze with DFS visited nodes:\n   ";
    cout << "\n   " << string(3*15, '-') << "\n";
    for (int i = 0; i < 15; i++) {
        cout << (i < 10 ? " " : "") << i << "| ";
        for (int j = 0; j < 15; j++) {
            if (i == startX && j == startY) {
                // Print the start position
                cout << "S ";
            } else if (i == endX && j == endY) {
                // Print the end position
                cout << "E ";
            } else if (maze[i][j] == 1) {
                // Print wall
                cout << "# ";
            } else if (visitedDFS[i][j]) {
                // Print DFS visited node in yellow
                cout << COLOR_YELLOW <<"D "<<COLOR_RESET;
            } else {
                // Print unvisited path
                cout << ". ";
            }
        }
        cout << "\n";
    }

    // Print the maze with BFS visited nodes highlighted
    cout << "\nMaze with BFS visited nodes:\n   ";
    cout << "\n   " << string(3*15, '-') << "\n";
    for (int i = 0; i < 15; i++) {
        cout << (i < 10 ? " " : "") << i << "| ";
        for (int j = 0; j < 15; j++) {
            if (i == startX && j == startY) {
                // Print the start position
                cout << "S ";
            } else if (i == endX && j == endY) {
                // Print the end position
                cout << "E ";
            } else if (maze[i][j] == 1) {
                // Print wall
                cout << "# ";
            } else if (visitedBFS[i][j]) {
                // Print BFS visited node in green
                cout << COLOR_GREEN << "B " << COLOR_RESET;
            } else {
                // Print unvisited path
                cout << ". ";
            }
        }
        cout << "\n";
    }

    return 0;
}

