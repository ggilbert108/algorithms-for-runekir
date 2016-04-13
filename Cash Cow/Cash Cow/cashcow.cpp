#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void printBoard(char board[12][10])
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

int changeBubbles(char board[12][10], int r, int c, char colorFrom, char colorTo)
{
	if (r < 0 || c < 0 || r >=12 || c >= 10)
		return 0;
	if (board[r][c] != colorFrom)
		return 0;

	board[r][c] = colorTo;

	return 1 +
	changeBubbles(board, r + 1, c, colorFrom, colorTo) +
	changeBubbles(board, r - 1, c, colorFrom, colorTo) +
	changeBubbles(board, r, c + 1, colorFrom, colorTo) +
	changeBubbles(board, r, c - 1, colorFrom, colorTo);
}

void settle(char board[12][10])
{
	for (int col = 0; col < 10; col++)
	{
		for (int row = 10; row >= 0; row--) 
		{
			int r = row;
			while (r < 11 && board[r][col] != ' ' && board[r + 1][col] == ' ')
			{
				board[r + 1][col] = board[r][col];
				board[r][col] = ' ';
				r++;
			}
		}
	}
}

bool emptyCol(char board[12][10], int col)
{
	for (int r = 0; r < 12; r++)
	{
		if (board[r][col] != ' ')
			return false;
	}
	return true;
}

void swapCols(char board[12][10], int col1, int col2)
{
	for (int r = 0; r < 12; r++)
	{
		char temp = board[r][col1];
		board[r][col1] = board[r][col2];
		board[r][col2] = temp;
	}
}

void shiftLeft(char board[12][10])
{
	for (int col = 1; col < 10; col++)
	{
		int c = col;
		while (c > 0 && emptyCol(board, c - 1) && !emptyCol(board, c))
		{
			swapCols(board, c - 1, c);
			c--;
		}
	}
}

void processTurn(char board[12][10], int clickRow, int clickCol)
{
	char color = board[clickRow][clickCol];

	if (color != ' ')
	{
		int numBubbles = changeBubbles(board, clickRow, clickCol, color, 'x');
		if (numBubbles < 3)
		{
			changeBubbles(board, clickRow, clickCol, 'x', color);
			return;
		}
		else
		{
			changeBubbles(board, clickRow, clickCol, 'x', ' ');
		}

		settle(board);
		shiftLeft(board);
	}


	cout << endl << endl;
}

int countBubbles(char board[12][10])
{
	int count = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (board[i][j] != ' ')
				count++;
		}
	}
	return count;
}

void main()
{
	ifstream fin("cashcow.in");

	if (fin)
	{
		ofstream fout("cashcow.out");

		int numTurns;

		fin >> numTurns;
		while (numTurns > 0)
		{
			char board[12][10] {{ ' ' }};

			string line;
			getline(fin, line);
			for (int i = 0; i < 12; i++)
			{
				getline(fin, line);

				for (int j = 0; j < 10; j++)
				{
					board[i][j] = line[j];
				}
			}

			for (int i = 0; i < numTurns; i++)
			{
				char col;
				int row;
				fin >> col >> row;
				col -= 'a';
				row = 12 - row;
				processTurn(board, row, col);
			}

			fout << countBubbles(board) << endl;
			
			fin >> numTurns;
		}
		fin.close();
		fout.close();
	}
}