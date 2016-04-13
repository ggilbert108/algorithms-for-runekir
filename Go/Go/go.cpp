#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int floodFill(const vector<vector<char>>& board, vector<vector<bool>>& visited, int r, int c, bool& touchesWhite, bool& touchesBlack)
{
	if (r < 0 || c < 0 || r >= board.size() || c >= board.size())
		return 0;

	if (board[r][c] == 'b')
	{
		touchesBlack = true;
		return 0;
	}
	if (board[r][c] == 'w')
	{
		touchesWhite = true; 
		return 0;
	}

	if (visited[r][c])
		return 0;
	visited[r][c] = true;


	return 1 +
		floodFill(board, visited, r + 1, c, touchesWhite, touchesBlack) +
		floodFill(board, visited, r - 1, c, touchesWhite, touchesBlack) +
		floodFill(board, visited, r, c + 1, touchesWhite, touchesBlack) +
		floodFill(board, visited, r, c - 1, touchesWhite, touchesBlack);
}


void scoreBoard(const vector<vector<char>>& board, int& whiteScore, int& blackScore)
{
	whiteScore = blackScore = 0;

	vector<vector<bool>> visited(board.size(), vector<bool>(board.size(), false));

	for (unsigned int i = 0; i < board.size(); i++)
	{
		for (unsigned int j = 0; j < board.size(); j++)
		{
			if (!visited[i][j] && board[i][j] == ' ')
			{
				bool touchesWhite = false;
				bool touchesBlack = false;

				int score = floodFill(board, visited, i, j, touchesWhite, touchesBlack);
				if (touchesWhite && !touchesBlack)
				{
					whiteScore += score;
				}
				else if (touchesBlack && !touchesWhite)
				{
					blackScore += score;
				}
			}
		}
	}
}

void main()
{
	ifstream fin("go.in");

	if (fin)
	{
		ofstream fout("go.out");
		
		int n, b, w;
		fin >> n;
		while (n > 0)
		{
			fin >> b >> w;

			vector<vector<char>> board (n, vector<char>(n, ' '));
			for (int i = 0; i < b; i++)
			{
				int x, y;
				fin >> y >> x;
				board[y - 1][x - 1] = 'b';
			}

			for (int i = 0; i < w; i++)
			{
				int x, y;
				fin >> y >> x;
				board[y - 1][x - 1] = 'w';
			}

			int blackScore = 0;
			int whiteScore = 0;

			scoreBoard(board, whiteScore, blackScore);

			int difference = whiteScore - blackScore;
			if (whiteScore > blackScore)
			{
				fout << "white wins by " << difference << endl;
			}
			else if (blackScore > whiteScore)
			{
				fout << "black wins by " << -difference << endl;
			}
			else
			{
				fout << "draw" << endl;
			}

			fin >> n;
		}
		fin.close();
		fout.close();
	}
	else
	{
		cout << "Cannot find file" << endl;
	}
}
