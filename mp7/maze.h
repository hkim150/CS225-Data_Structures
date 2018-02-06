/* Your code here! */

#ifndef __MAZE_H__
#define __MAZE_H__

#include <vector>
#include <time.h>
#include <queue>
#include "png.h"
#include "dsets.h"

class SquareMaze{
private:
    int width, height;
    int exit;
    std::vector<bool> downWall;
    std::vector<bool> rightWall;

public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    std::vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
};

#endif

