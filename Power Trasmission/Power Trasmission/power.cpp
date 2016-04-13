#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include "assert.h"
#define INF 100000000
using namespace std;

struct State
{
	vector<int> path;
	int minCapacity;

	string toString()
	{
		string result = "";
		for (int i = 0; i < path.size(); i++)
		{
			result += to_string(path[i]) + " ";
		}
		return result;
	}
};

vector<int> shortestPath(vector<vector<int>> matrix, int& minCapacity)
{
	queue<State> q;
	State original;
	original.path.push_back(0);
	original.minCapacity = INF;
	q.push(original);

	unordered_set<string> breadcrumbs;
	breadcrumbs.insert("0 ");
		
	while(q.size() > 0)
	{
		State state = q.front(); q.pop();
		int lastNode = state.path[state.path.size() - 1];

		cout << state.toString() << endl;
		if(lastNode == matrix.size() - 1)
		{
			minCapacity = state.minCapacity;
			return state.path;
		}

		for (int i = 0; i < matrix.size(); i++)
		{
			if (matrix[lastNode][i] <= 0)
				continue;
			State newState;
			newState.path = state.path;
			int newCapacity = matrix[lastNode][i];
			newState.path.push_back(i);

			if(newCapacity < state.minCapacity)
			{
				newState.minCapacity = newCapacity;
			}
			else
			{
				newState.minCapacity = state.minCapacity;
			}
			string stringRep = newState.toString();
			if(breadcrumbs.find(stringRep) == breadcrumbs.end())
			{
				q.push(newState);
				breadcrumbs.insert(stringRep);
			}
		}
	}
	return vector<int>();
}

int maxFlow(vector<int>& capacities, vector<vector<int>>& matrix)
{
	int minCapacity = 0;
	vector<int> path = shortestPath(matrix, minCapacity);
	int flow = 0;
	while(path.size() > 0)
	{
		flow += minCapacity;
		for (int i = 0; i < path.size() - 1; i++)
		{
			int from = path[i];
			int to = path[i + 1];

			matrix[from][to] -= minCapacity;
			matrix[to][from] += minCapacity;
		}
		path = shortestPath(matrix, minCapacity);
	}
	return flow;
}

void main()
{
	ifstream fin("power.in");
	ofstream fout("power.out");
	assert(fin);

	int numRegulators;

	fin >> numRegulators;
	while(numRegulators > 0)
	{
		vector<int> capacities(numRegulators);

		for (int i = 0; i < numRegulators; i++)
		{
			fin >> capacities[i];
		}

		int numLinks;
		fin >> numLinks;

		vector<vector<int>> matrix(numRegulators + 2, vector<int>(numRegulators + 2, 0));
		for (int i = 0; i < numLinks; i++)
		{
			int from, to, capacity;
			fin >> from >> to >> capacity;

			matrix[from][to] = capacity;
		}

		int L, R;
		fin >> L >> R;

		for (int i = 0; i < L; i++)
		{
			int reg;
			fin >> reg;
			matrix[0][reg] = INF;
		}
		for (int i = 0; i < R; i++)
		{
			int reg;
			fin >> reg;
			matrix[reg][numRegulators + 1] = INF;
		}

		cout << maxFlow(capacities, matrix) << endl;

		fin >> numRegulators;
	}
	fin.close();
	fout.close();
}