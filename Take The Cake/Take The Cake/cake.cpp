#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int getMaxLayers(const vector<int>& layers)
{
	vector<int> dp(layers.size());

	int max = 0;
	for (int i = 0; i < dp.size(); i++)
	{
		int highest = 0;
		for (int j = 0; j < i; j++)
		{
			if (dp[j] > highest && layers[j] >= layers[i])
			{
				highest = dp[j];
			}
		}
		dp[i] = highest + 1;
		if (dp[i] > max)
		{
			max = dp[i];
		}
	}

	return max;
}

void main()
{
	ifstream fin("cake.in");
	
	if (fin)
	{
		ofstream fout("cake.out");

		int numLayers;
		fin >> numLayers;

		while (numLayers > 0)
		{
			vector<int> layers(numLayers);

			for (int i = 0; i < numLayers; i++)
			{
				int size;
				fin >> size;

				layers[i] = size;
			}

			int maxLayers = getMaxLayers(layers);
			fout << maxLayers << endl;

			fin >> numLayers;
		}

		fin.close();
		fout.close();
	}
}