#include "MazeSolver.h"
#include <stack>
#include <queue>

bool MazeSolver::solveDFS(Maze& maze, int sx, int sy, int ex, int ey) {
    // DFS stack
    stack<pair<int, int>> st;
    st.push({sx, sy});

    while (!st.empty()) {
        auto [x, y] = st.top();
        st.pop();

        if (!maze.isValid(x, y)) continue;

        maze.markVisited(x, y);

        if (x == ex && y == ey)
            return true;

        st.push({x + 1, y});
        st.push({x - 1, y});
        st.push({x, y + 1});
        st.push({x, y - 1});
    }
    return false;
}

bool MazeSolver::solveBFS(Maze& maze, int sx, int sy, int ex, int ey) {
    queue<pair<int, int>> q;
    q.push({sx, sy});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (!maze.isValid(x, y)) continue;

        maze.markVisited(x, y);

        if (x == ex && y == ey)
            return true;

        q.push({x + 1, y});
        q.push({x - 1, y});
        q.push({x, y + 1});
        q.push({x, y - 1});
    }
    return false;
}
