#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "PathfinderInterface.h"
using namespace std;

const int ROW_SIZE = 5;
const int COL_SIZE = 5;
const int HEIGHT_SIZE = 5;
const int BACKGROUND = 1;
const int WALL = 0;
const int TEMPORARY = 2; // Used to show this path has been explored
const int PATH = 3;

class Pathfinder : public PathfinderInterface
{
    
//private: 

protected:
  int maze_grid[ ROW_SIZE ][ COL_SIZE ][ HEIGHT_SIZE ]; // To hold values
  int default_grid[ ROW_SIZE ][ COL_SIZE ][ HEIGHT_SIZE ];
  vector<string> solution;
  bool imported;
    
public:
	Pathfinder();
	~Pathfinder();
	
	string toString() const;
	
	string toString();

	void createRandomMaze();
	
	bool importMaze(string file_name);
	
	vector<string> solveMaze();
	
	bool find_maze_path(int grid[ROW_SIZE][COL_SIZE][HEIGHT_SIZE], int r, int c, int h);
	
};