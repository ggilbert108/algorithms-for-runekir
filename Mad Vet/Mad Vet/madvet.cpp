#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <hash_set>
#include <set>
using namespace std;

typedef vector<int> AnimalCounts;

struct Machine
{
	AnimalCounts input;
	AnimalCounts output;

	Machine()
	{
		input = AnimalCounts(3);
		output = AnimalCounts(3);
	}
};

struct State
{
	AnimalCounts animals;
	int numSteps;
};

bool convertAnimals(const Machine& machine, const AnimalCounts& animals, bool reverse, AnimalCounts& result)
{
	AnimalCounts input = (reverse) ? machine.output : machine.input;
	AnimalCounts output = (reverse) ? machine.input : machine.output;

	for (int i = 0; i < 3; i++)
	{
		result[i] -= input[i];

		if (result[i] < 0)
		{
			return false;
		}

		result[i] += output[i];
	}

	return true;
}

int getMinSteps(Machine machines[3], const AnimalCounts& given, const AnimalCounts& expected)
{
	set<AnimalCounts> breadcrumbs;

	queue<State> queue;
	State original = { given, 0 };
	queue.push(original);

	while (!queue.empty())
	{
		State state = queue.front(); queue.pop();

		if (state.animals == expected)
		{
			return state.numSteps;
		}
		else if (state.numSteps >= 100)
		{
			return -1;
		}

		for (int i = 0; i < 3; i++)
		{
			Machine machine = machines[i];
			for (int j = 0; j <= 1; j++)
			{
				bool reverse = (j == 0) ? false : true;

				AnimalCounts result = state.animals;
				if (convertAnimals(machine, state.animals, reverse, result))
				{
					if (breadcrumbs.find(result) == breadcrumbs.end())
					{
						breadcrumbs.insert(result);
						State child = { result, state.numSteps + 1 };
						queue.push(child);
					}
				}
			}
		}
	}

	return -1;
}

void main()
{
	ifstream fin("madvet.in");

	if (fin)
	{
		ofstream fout("madvet.out");

		int numDataSets;
		fin >> numDataSets;

		while (numDataSets-- > 0)
		{
			int setNumber, numQuestions;

			fin >> setNumber >> numQuestions;

			Machine machines[3];
			machines[0].input[0] = 1;
			machines[1].input[1] = 1;
			machines[2].input[2] = 1;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					int numOutput;
					fin >> numOutput;
					machines[i].output[j] = numOutput;
				}
			}
			
			fout << setNumber << " " << numQuestions << endl;

			for (int i = 0; i < numQuestions; i++)
			{
				int questionNumber; fin >> questionNumber;
				AnimalCounts given(3);
				AnimalCounts expected(3);
				for (int j = 0; j < 3; j++)
				{
					int amount;
					fin >> amount;
					given[j] = amount;;
				}
				for (int j = 0; j < 3; j++)
				{
					int amount;
					fin >> amount;
					expected[j] = amount;;
				}

				int minSteps = getMinSteps(machines, given, expected);
				fout << questionNumber << " ";

				if (minSteps >= 0)
				{
					fout << minSteps << endl;
				}
				else
				{
					fout << "NO SOLUTION" << endl;
				}
			}

		}

		fin.close();
		fout.close();
	}
}