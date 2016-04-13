#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
using namespace std;

#define W 0
#define NW 1
#define N 2
#define NE 3
#define E 4
#define SE 5
#define S 6
#define SW 7

typedef vector<vector<bool>> Bitmap;

struct Coord
{
	int r, c;

	bool operator==(const Coord& rValue)
	{
		return r == rValue.r && c == rValue.c;
	}
};

int removeObject(vector<vector<bool>>& bitmap, int r, int c)
{
	if (r < 0 || c < 0 || r >= bitmap.size() || c >= bitmap[0].size())
		return 0;
	if (bitmap[r][c] == 0)
		return 0;
	bitmap[r][c] == 0;

	return 1 +
	removeObject(bitmap, r + 1, c) +
	removeObject(bitmap, r - 1, c) + 
	removeObject(bitmap, r, c + 1) +
	removeObject(bitmap, r, c - 1);
}

void findFirstObject(Coord center, Bitmap& bitmap,  int& direction, Coord& firstObject, Coord& prevToFirstObject)
{
	list<int> deltaR {0, -1, -1, -1, 0, 1, 1, 1};
	list<int> deltaC {-1, -1, 0, 1, 1, 1, 0, -1};

	for (int i = 0; i < direction; i++)
	{
		int temp = deltaR.front();
		deltaR.pop_front();
		deltaR.push_back(temp);

		temp = deltaC.front();
		deltaC.pop_front();
		deltaC.push_back(temp);
	}

	list<int>::iterator deltaRIt = deltaR.begin();
	list<int>::iterator deltaCIt = deltaR.end();

	for (int i = 0; i < 8; i++)
	{
		direction = (direction + 1) % 8;

		int dr = deltaR.front();
		int dc = deltaC.front();
		deltaR.pop_front();
		deltaC.pop_front();

		int row = center.r + dr;
		int col = center.c + dc;

		Coord coord = { row, col };

		if (bitmap[coord.r][coord.c])
		{
			firstObject = coord;
			return;
		}
		prevToFirstObject = coord;
	}
}

int countContour(Bitmap& bitmap, int row, int col)
{
	int length = 0;

	Coord b0 = { row, col };
	Coord c0 = { row - 1, col };

	Coord b1;
	Coord c1;

	int direction = W;

	findFirstObject(b0, bitmap, direction, b1, c1);

	Coord b = b1;
	Coord c = c1;

	bool foundB0 = false;
	bool nextIsB1 = false;
	while (!(foundB0 && nextIsB1))
	{
		cout << b.r << " " << b.c << endl;

		Coord bk;
		Coord ck;
		findFirstObject(b, bitmap, direction, bk, ck);

		b = bk;
		c = ck;

		length++;

		if (b == b0)
		{
			foundB0 = true;
		}
		if (foundB0 == true && b == b1)
		{
			nextIsB1 = true;
		}
	}

	return length;
}

vector<int> countContours(Bitmap& bitmap)
{
	vector<int> lengths;

	for (unsigned int i = 0; i < bitmap.size(); i++)
	{
		for (unsigned int j = 0; j < bitmap[0].size(); j++)
		{
			if (bitmap[i][j] == 1)
			{
				int length = countContour(bitmap, i, j);
				int size = removeObject(bitmap, i, j);

				if (size >= 5)
				{
					lengths.push_back(length);
				}
			}
		}
	}

	sort(lengths.begin(), lengths.end());

	return lengths;
}

void main()
{
	ifstream fin("contour.in");

	if (fin)
	{
		ofstream fout("contour.out");

		int rows, cols;
		fin >> rows >> cols;

		while (rows != 0 && cols != 0)
		{
			vector<vector<bool>> bitmap(rows, vector<bool>(cols, false));

			string line;
			getline(fin, line);
			for (int i = 0; i < rows; i++)
			{
				getline(fin, line);
				for (unsigned int j = 0; j < line.length(); j++)
				{
					if (line[j] == '1')
						bitmap[i][j] = true;
				}
			}

			vector<int> counts = countContours(bitmap);
			sort(counts.begin(), counts.end());

			for each (int n in counts)
			{
				cout << n << " ";
			}
			cout << endl;

			fin >> rows >> cols;
		}

		fin.close();
		fout.close();
	}
}