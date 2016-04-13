#include <iostream>
#include <fstream>
#include "assert.h"
using namespace std;

void main()
{
	ifstream fin("mazecost.in");
	ofstream fout("mazecost.out");

	assert(fin);

	int mazes;
	fin >> mazes;

	for (int i = 0; i < mazes; i++)
	{
		int rows;
		int cols;
		fin >> rows >> cols;

		int total = 0;
		for (int i = 0; i < rows * cols; i++)
		{
			char ch;
			fin >> ch;

			if(ch == 'X')
			{
				total += 50;
			}
			else if (ch == '-')
			{
				total += 10;
			}
			else if(ch == '+')
			{
				total += 500;
			}
		}
		fout << total << endl;
	}
}