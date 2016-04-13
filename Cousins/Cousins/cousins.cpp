#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int countCousins(const vector<int>& nodes, const vector<int>& parents, int nodeValue)
{
	int nodeIndex = -1;
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i] == nodeValue)
		{
			nodeIndex = i;
			break;
		}
	}

	int parentIndex = parents[nodeIndex];
	int grandIndex = 0;
	if (parentIndex != -1)
	{
		grandIndex = parents[parentIndex];
	}
	else
	{
		return 0;
	}

	int count = 0;
	for (unsigned int i = 0; i < nodes.size(); i++)
	{
		if (i == nodeIndex) continue;

		int pIndex = parents[i];
		if (pIndex == -1) continue;

		int gpIndex = parents[pIndex];

		if (pIndex != parentIndex && gpIndex == grandIndex)
			count++;
	}

	return count;
}

int main()
{
	ifstream fin("cousins.in");

	if (fin)
	{
		ofstream fout("cousins.out");

		int n, k;
		fin >> n >> k;

		while (n != 0 && k != 0)
		{
			vector<int> nodes(n);
			vector<int> parents(n);
			int parentIndex = -1;
			for (int i = 0; i < n; i++)
			{
				int nodeData;
				fin >> nodeData;

				if (i > 0 && (nodeData - nodes[i - 1]) > 1)
				{
					parentIndex++;
				}

				nodes[i] = nodeData;
				parents[i] = parentIndex;
			}

			int result = countCousins(nodes, parents, k);
			
			fout << result << endl;

			fin >> n >> k;
		}

		fin.close();
		fout.close();
	}
	else
	{
		cout << "input file not found" << endl;
	}
}