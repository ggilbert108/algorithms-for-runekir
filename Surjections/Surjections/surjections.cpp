#include <iostream>
#include <fstream>
using namespace std;


long long power(int b, int n)
{
	long long total = 1;
	for (int i = 0; i < n; i++)
		total *= b;
	return total;
}

long long combination(long long n, long long i)
{
	if (i == 0 || n == 0 || i == n)
		return 1;

	return combination(n - 1, i - 1) + combination(n - 1, i);
}

long long factorial(long long n)
{
	long long total = 1;
	for (int i = 1; i <= n; i++)
		total *= i;
	return total;
}

long long S(long long m, long long n)
{
	if (n == 1)
		return 1;
	if (m < n)
		return 0;
	if (m == n)
		return factorial(m);
	
	long long result = power(n, m);

	for (int i = 1; i < n; i++)
	{
		result -= combination(n, i) * S(m, i);
	}

	return result;
}

void main() {
	ifstream fin("surjections.in");
	if (fin) 
	{
		ofstream fout("surjections.out");

		int n;
		int m;

		fin >> m >> n;

		while (n > 0 && m > 0)
		{
			long long result = S(m, n);
			fout << "S(" << m << "," << n << ") = " << result << endl;
			fin >> m >> n;
		}

		fout.close();
		fin.close();
	}
	else 
	{
		cout << "Input file not found." << endl;
	}
}