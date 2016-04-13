#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

typedef vector<string> Maze;

bool move(const Maze& maze, char& dir, int row, int col, bool player, Maze& result)
{
	int newRow = row;
	int newCol = col;
	
	if (dir == 'n')
		newRow--;
	if (dir == 's')
		newRow++;
	if (dir == 'e')
		newCol--;
	if (dir == 'w')
		newCol++;

	if (newRow < 0 || newCol < 0 || newRow >= maze.size() || newCol >= maze[0].size())
		return false;
	if (maze[newRow][newCol] == '#')
		return false;
	
	if (player && maze[newRow][newCol] == 'B')
	{
		if (move(maze, dir, newCol, newRow, false, result))
			dir = toupper(dir);
	}

	char ch = maze[row][col];
	result[newRow][newCol] = ch;
	result[row][col] = '.';

	return false;
}

string solveMaze(const Maze& maze)
{
	for (int i = 0; i < maze.size(); i++)
	{
		cout << maze[i] << endl;
	}

	return "";
}

void main()
{
	ifstream fin("boxes.in");

	if (fin)
	{
		ofstream fout("boxes.out");

		int rows, cols;
		fin >> rows >> cols;

		string line;
		getline(fin, line); //to get the end of line character

		while (rows != 0 && cols != 0)
		{
			Maze maze(rows);
			for (int i = 0; i < rows; i++)
			{
				getline(fin, line);
				maze[i] = line;
			}

			solveMaze(maze);

			fin >> rows >> cols;
			getline(fin, line); //to get the end of line character
		}

		fin.close();
		fout.close();
	}
}