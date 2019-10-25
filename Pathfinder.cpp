#include "Pathfinder.h"
using namespace std;

Pathfinder::Pathfinder() {
    srand(time(NULL));
    
    ifstream file("filler.txt");
	if (file.is_open()) {
		string line;
		for (int height = 0; height < HEIGHT_SIZE; height++) {
			for(int row = 0; row < ROW_SIZE; row++) {
				getline(file, line);
				if (line.empty()) {
				    getline(file, line);
				}
				stringstream ss(line);
				for(int col = 0; col < COL_SIZE; col++) {
					int value;
					ss >> value;
					default_grid[row][col][height] = value;
				}
			}
		}
    }
    file.close();
}
Pathfinder::~Pathfinder() {}

//Part 1-----------------------------------------------------------------------------------
/*
* toString
*
* Returns a string representation of the current maze. Returns a maze of all 1s if no maze
* has yet been generated or imported.
*
* A valid string representation of a maze consists only of 125 1s and 0s (each separated
* by spaces) arranged in five 5x5 grids (each separated by newlines) with no trailing newline. A valid maze must
* also have 1s in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).
*
* Cell (0, 0, 0) is represented by the first number in the string representation of the
* maze. Increasing in x means moving toward the east, meaning cell (1, 0, 0) is the second
* number. Increasing in y means moving toward the south, meaning cell (0, 1, 0) is the
* sixth number. Increasing in z means moving downward to a new grid, meaning cell
* (0, 0, 1) is the twenty-sixth cell in the maze. Cell (4, 4, 4) is represented by the last number.
*
* Returns:		string
*				A single string representing the current maze
*/
string Pathfinder::toString() const {
}

string Pathfinder::toString() {
    stringstream ss;
    
     if (imported == true) {
        for (int height = 0; height < HEIGHT_SIZE; height++) {
    	    for(int row = 0; row < ROW_SIZE; row++) {
    	        for(int col = 0; col < COL_SIZE; col++) {
    	            if (col == COL_SIZE - 1) {
    	                ss << maze_grid[row][col][height];
    	            }
    	            else {
    	                ss << maze_grid[row][col][height] << " ";
    	            }
    	        }
    	        ss << endl;
    	    }
    	    if (height != HEIGHT_SIZE - 1) {
    	        ss << endl;
    	    }
        }
    }
    else {
        for (int height = 0; height < HEIGHT_SIZE; height++) {
    	    for(int row = 0; row < ROW_SIZE; row++) {
    	        for(int col = 0; col < COL_SIZE; col++) {
    	            if (col == COL_SIZE - 1) {
    	                ss << default_grid[row][col][height];
    	            }
    	            else {
    	                ss << default_grid[row][col][height] << " ";
    	            }
    	        }
    	        ss << endl;
    	    }
    	    if (height != HEIGHT_SIZE - 1) {
    	        ss << endl;
    	    }
        }
    }
    
    imported = false;
    return ss.str();
}

/*
* createRandomMaze
*
* Generates a random maze and stores it as the current maze.
*
* The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
* in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).  The generated maze may be
* solvable or unsolvable, and this method should be able to produce both kinds of mazes.
*/
void Pathfinder::createRandomMaze() {
    imported = true;
    for (int height = 0; height < HEIGHT_SIZE; height++) {
        for(int row = 0; row < ROW_SIZE; row++) {
	        for(int col = 0; col < COL_SIZE; col++) {
	            maze_grid[row][col][height] = (rand() % 2);
	        }
	    }
    }
    maze_grid[0][0][0] = 1;
    maze_grid[ROW_SIZE - 1][COL_SIZE - 1][HEIGHT_SIZE - 1] = 1;
}

//Part 2-----------------------------------------------------------------------------------
/*
* importMaze
*
* Reads in a maze from a file with the given file name and stores it as the current maze.
* Does nothing if the file does not exist or if the file's data does not represent a valid
* maze.
*
* The file's contents must be of the format described above to be considered valid.
*
* Parameter:	file_name
*				The name of the file containing a maze
* Returns:		bool
*				True if the maze is imported correctly; false otherwise
*/
bool Pathfinder::importMaze(string file_name) {
    
	    int count = 0;
	    int temp_maze[ROW_SIZE][COL_SIZE][HEIGHT_SIZE];
		ifstream file(file_name.c_str());
		
		if (file.is_open()) {
			string line;
			for (int height = 0; height < HEIGHT_SIZE; height++) {
    			for(int row = 0; row < ROW_SIZE; row++) {
    				getline(file, line);
    				if (line.empty()) {
    				    getline(file, line);
    				}
    				stringstream ss(line);
    				for(int col = 0; col < COL_SIZE; col++) {
    					int value;
    					ss >> value;
    					count++;
    					if (value == 1 || value == 0) {
        					temp_maze[row][col][height] = value;
    					}
    					else {
    					    imported = true;
    					    return(false);
    					}
    				}
    			}
			}
			while (!(file.eof())) {
			    int excess;
			    getline(file, line);
			    stringstream ss(line);
			    int value;
			    ss >> value;
			    if (value == 1) {
			        imported = true;
			        return(false);
			    }
			}
			if (count == 125 && temp_maze[0][0][0] == 1 && temp_maze[ROW_SIZE - 1][COL_SIZE - 1][HEIGHT_SIZE - 1]){
			    copy(begin(temp_maze), end(temp_maze), begin(maze_grid));
			    imported == false;
			    return(true);
			}
			else {
			    imported = true;
			    return(false);
			}
		}
		else {
		    imported = true;
		    return(false);
		}
	}

//Part 3-----------------------------------------------------------------------------------
/*
* solveMaze
*
* Attempts to solve the current maze and returns a solution if one is found.
*
* A solution to a maze is a list of coordinates for the path from the entrance to the exit
* (or an empty vector if no solution is found). This list cannot contain duplicates, and
* any two consecutive coordinates in the list can only differ by 1 for only one
* coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
* in the solution. Each string in the solution vector must be of the format "(x, y, z)",
* where x, y, and z are the integer coordinates of a cell.
*
* Understand that most mazes will contain multiple solutions
*
* Returns:		vector<string>
*				A solution to the current maze, or an empty vector if none exists
*/
vector<string> Pathfinder::solveMaze() {
    solution.clear();
    find_maze_path(maze_grid, 0, 0, 0);
    //imported = true;
    return solution;
}

bool Pathfinder::find_maze_path(int grid[HEIGHT_SIZE][ROW_SIZE][COL_SIZE], int r, int c, int h) {
    if (r < 0 || c < 0 || h < 0 || r >= ROW_SIZE || c >= COL_SIZE || h >= HEIGHT_SIZE) //error check
        return false;
    else if (grid[r][c][h] != BACKGROUND) //error check
        return false;
    else if (r == ROW_SIZE - 1 && c == COL_SIZE - 1 && h == HEIGHT_SIZE - 1) /*base case*/ {
        grid[r][c][h] = PATH;
        solution.insert(solution.begin(), "(" + to_string(r) + ", " + to_string(c) + ", " + to_string(h) + ")");
        for (int height = 0; height < HEIGHT_SIZE; height++) {
    	    for(int row = 0; row < ROW_SIZE; row++) {
    	        for(int col = 0; col < COL_SIZE; col++) {
    	            if (grid[row][col][height] == 2)
    	                grid[row][col][height] = 1;
    	        }
    	    }
        }
        return true;
    } 
    else /*recursive case*/ {
        grid[r][c][h] = PATH;
        if (find_maze_path(grid, r - 1, c, h)
        || find_maze_path(grid, r + 1, c, h)
        || find_maze_path(grid, r, c - 1, h)
        || find_maze_path(grid, r, c + 1, h)
        || find_maze_path(grid, r, c, h - 1)
        || find_maze_path(grid, r, c, h + 1)) {
              solution.insert(solution.begin(), "(" + to_string(r) + ", " + to_string(c) + ", " + to_string(h) + ")");
             return true;
        }
        else {
            grid[r][c][h] = TEMPORARY;
            return false;
        }
    }
    
}