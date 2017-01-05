#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

class Cell
{
	public :
		int row;
		int column;
};

class mazeSolver
{
	public:
		int rows, cols;
		Cell start, finish;
		bool isPath;
		vector<Cell> path;
		void toSolve(bool **maze);
		bool solve_recursive(bool **maze, int currentRow,int currentCol, int previousRow, int previousCol);
		void toString(bool **maze);
		
};

int main()
{
	ifstream in;
	in.open("sampleMaze.txt");
	
	if (in.fail())
	{
		cout << "Error Reading Maze!\n";
		return 0;
	}
	
	Cell tempcell;
	string tempstr;
	char tempchr;
	
	mazeSolver mymaze;
	
	// getting headers
	in >> tempstr >> mymaze.rows >> tempstr >> mymaze.cols;
	in >> tempstr >> tempchr >> mymaze.start.row >> tempchr >> mymaze.start.column >> tempchr; 
	in >> tempstr >> tempchr >> mymaze.finish.row >> tempchr >> mymaze.finish.column >> tempchr; 
	
	// generating maze
	bool **maze = new bool*[mymaze.rows];
	for (int i = 0; i < mymaze.rows; i++)
	{
		maze[i] = new bool[mymaze.cols];
	}
	for (int i = 0; i < mymaze.rows; i++)
	{
		for (int j = 0; j < mymaze.cols; j++)
		{
			maze[i][j] = false;
		}
	}
		
	
	// filling in the available paths
	while (!in.eof())
	{
		in >> tempchr >> tempcell.row >> tempchr >> tempcell.column >> tempchr;
		maze[tempcell.row][tempcell.column] = true; 
	}
	in.close();
	
	// Printing the maze
		cout << " ";
		for (int i = 0; i < mymaze.cols; i++)
		{
			cout << i;
		}
		cout << endl;
		for (int i = 0; i < mymaze.rows; i++)
		{
			cout << i;
			for (int j = 0; j < mymaze.cols; j++)
			{
				if (maze[i][j] == true)
				{
					cout << " ";
				}
				else
				{
					cout << "#";
				}
			}
			cout << endl;
		}
		cout << endl << endl;
	mymaze.toSolve(maze);
	mymaze.toString(maze);
}

void mazeSolver::toSolve(bool **maze)
{
	Cell temp;
	temp.row = start.row;
	temp.column = start.column;
	path.push_back(temp);
	bool success = false;
	if ((start.row != 0) && (maze[start.row - 1][start.column] == true))
	{
		success = solve_recursive(maze, start.row - 1, start.column, start.row, start.column);
	}
	else if ((start.column != 0) && (maze[start.row][start.column - 1] == true))
	{
		success = solve_recursive(maze, start.row, start.column - 1, start.row, start.column);
	}
	else if ((start.row != rows - 1) && (maze[start.row + 1][start.column] == true))
	{
		success = solve_recursive(maze, start.row + 1, start.column, start.row, start.column);
	}
	else if ((start.column != cols - 1) && (maze[start.row][start.column + 1] == true))
	{
		success = solve_recursive(maze, start.row, start.column + 1, start.row, start.column);
	}
	else
	{
		success = false;
	}
	
	if (success == true)
	{
		isPath = true;
		toString(maze);
		exit(1);
	}
	else
	{
		isPath = false;
		toString(maze);
		exit(1);
	}
	
}

bool mazeSolver::solve_recursive(bool **maze, int currentRow, int currentCol, int previousRow, int previousCol)
{
	Cell temp;
	temp.row = currentRow;
	temp.column = currentCol;
	
	path.push_back(temp);
		
	if (currentRow == finish.row && currentCol == finish.column)
	{
		return true;
	}
	
	if ((currentRow != 0) && (maze[currentRow - 1][currentCol] == true) && (currentRow - 1 != previousRow))
	{
		
		return solve_recursive(maze, currentRow - 1, currentCol, currentRow, currentCol);
	}
	else if ((currentCol != 0) && (maze[currentRow][currentCol - 1] == true) && (currentCol - 1 != previousCol))
	{
		
		return solve_recursive(maze, currentRow, currentCol - 1, currentRow, currentCol);
	}
	else if ((currentRow != rows - 1) && (maze[currentRow + 1][currentCol] == true) && (currentRow + 1 != previousRow))
	{
		
		return solve_recursive(maze, currentRow + 1, currentCol, currentRow, currentCol);
	}
	else if ((currentCol != cols - 1) && (maze[currentRow][currentCol + 1] == true) && (currentCol + 1 != previousCol))
	{
		
		return solve_recursive(maze, currentRow, currentCol + 1, currentRow, currentCol);
	}
	else if (maze[previousRow][previousCol] == true)
	{
		maze[currentRow][currentCol] = false;
		while (!path.empty())
		{
			path.pop_back();
		}
		
		toSolve(maze);
	}
	else
	{
		return false;
	}
	
}
		
void mazeSolver::toString(bool **maze)
{
	if (isPath == true)
	{
		cout << "Success" << endl << endl;
		cout << "[ ";
		for (int i = 0; i < path.size(); i++)
		{
			cout << "(" << path[i].row  << "," << path[i].column << ") ";
		}
		cout << "]";
	}
	else
	{
		cout << "No Path Found!\n";
	}

}
