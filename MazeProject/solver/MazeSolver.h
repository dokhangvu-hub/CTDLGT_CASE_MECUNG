#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "../core/Maze.h"
#include <vector>

using namespace std;

class MazeSolver {
public:
    static bool solveDFS(Maze& maze, int sx, int sy, int ex, int ey);
    static bool solveBFS(Maze& maze, int sx, int sy, int ex, int ey);
};

#endif
