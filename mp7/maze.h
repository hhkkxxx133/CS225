/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "png.h"
#include "rgbapixel.h"
#include "dsets.h"

#include <queue>

using namespace std;

class SquareMaze
{
public:
	SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	vector<int> solveMaze();
	PNG* drawMaze() const;
	PNG* drawMazeWithSolution();

private:
	int _width;
	int _height;
	int _size;

	DisjointSets _cells;

	vector<bool> _downwall;
	vector<bool> _rightwall;

	bool ** visited;

	void solve(int x, int y, vector<int> path, vector<vector<int>> & paths, vector<int> & end_x);
	
};

#endif