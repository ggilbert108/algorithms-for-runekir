#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<int> getDivisors(int n)
{
	vector<int> divisors;

	for (int i = 1; i < n; i++)
	{
		if (n % i == 0)
			divisors.push_back(i);
	}

	return divisors;
}

bool isSemiperfect(int n)
{
	//https://en.wikipedia.org/wiki/Subset_sum_problem

	vector<int> divisors = getDivisors(n);

	int sumDivisors = 0;
	for each(int x in divisors){
		sumDivisors += x;
	}

	vector<vector<bool>> dp(divisors.size(), vector<bool>(sumDivisors));

	for (int i = 1; i <= sumDivisors; i++)
	{
		dp[0][i-1] = (divisors[0] == i);
	}

	for (int i = 1; i < divisors.size(); i++)
	{
		for (int j = 1; j <= sumDivisors; j++)
		{
			bool isSum = dp[i - 1][j - 1] || divisors[i] == j;
			if ((j - 1) - divisors[i] >= 0)
			{
				isSum = isSum || dp[i - 1][(j - 1) - divisors[i]];
			}
			dp[i][j - 1] = isSum;
		}
	}

	if (n - 1 < sumDivisors)
	{
		return dp[dp.size() - 1][n - 1];
	}
	else
	{
		return false;
	}
}

void main()
{
	ifstream fin("semiperfect.in");

	if (fin)
	{
		ofstream fout("semiperfect.out");

		int n;
		fin >> n;

		while (n != 0)
		{
			fout << n << ":";
			if (isSemiperfect(n))
			{
				fout << "YES";
			}
			else
			{
				fout << "NO";
			}
			fout << endl;

			fin >> n;
		}

		fin.close();
		fout.close();
	}
}