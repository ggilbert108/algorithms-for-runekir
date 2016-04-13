#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

typedef vector<vector<int>> Plinko;

int getMaxScore(Plinko plinko)
{
	Plinko dp(plinko.size());

	for (int i = 0; i < plinko.size(); i++)
	{
		dp[i] = vector<int>(plinko[i].size());
	}

	for (int i = 0; i < plinko.size(); i++)
	{
		for (int j = 0; j < plinko[i].size(); j++)
		{
			if (i == 0)
			{
				dp[i][j] = plinko[i][j];
			}
			else if (j == 0)
			{
				dp[i][j] = plinko[i][j] + dp[i - 1][j];
			}
			else if (j == plinko[i].size() - 1)
			{
				dp[i][j] = plinko[i][j] + dp[i - 1][j - 1];
			}
			else
			{
				int maxScore = max(dp[i - 1][j], dp[i - 1][j - 1]);
				dp[i][j] = plinko[i][j] + maxScore;
			}
		}
	}

	int maxScore = 0;
	for (int i = 0; i < dp[dp.size() - 1].size(); i++)
	{
		int score = dp[dp.size() - 1][i];
		if (score > maxScore)
			maxScore = score;
	}

	return maxScore;
}

void main()
{
	ifstream fin("plinko.in");

	if (fin)
	{
		ofstream fout("plinko.out");

		int rows;
		fin >> rows;

		while (rows != 0)
		{
			Plinko plinko(rows);
			for (int i = 1; i <= rows; i++)
			{
				for (int j = 0; j < i; j++)
				{
					int n;
					fin >> n;
					plinko[i - 1].push_back(n);
				}
			}

			int result = getMaxScore(plinko);
			fout << result << endl;
			cout << result << endl;

			fin >> rows;
		}

		fin.close();
		fout.close();
	}
}