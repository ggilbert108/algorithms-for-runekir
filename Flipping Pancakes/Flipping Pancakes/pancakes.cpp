#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<hash_set>
using namespace std;

struct State
{
	string pancakes;
	int numFlips;
};

bool isInOrder(string pancakes)
{
	for (int i = 0; i < pancakes.length(); i++)
	{
		if (islower(pancakes[i]))
			return false;
		if (i > 0 && pancakes[i] < pancakes[i - 1])
			return false;
	}
	return true;
}

string flip(string pancakes, int n)
{
	n = pancakes.length() - n;
	string flipped = "";

	flipped += pancakes.substr(0, n);

	string flipPart = pancakes.substr(n);
	
	for (int i = flipPart.length() - 1; i >= 0; i--)
	{
		char ch = flipPart[i];

		if (isupper(ch))
		{
			ch = tolower(ch);
		}
		else
		{
			ch = toupper(ch);
		}

		flipped += ch;
	}

	return flipped;
}

int getMinFlips(string pancakes)
{
	hash_set<string> breadCrumbs;

	State original = {pancakes, 0};
	
	queue<State> q;
	q.push(original);

	while (!q.empty())
	{
		State state = q.front();
		q.pop();

		if (isInOrder(state.pancakes))
		{
			return state.numFlips;
		}

		for (int i = 1; i <= state.pancakes.length(); i++)
		{
			string childCakes = flip(state.pancakes, i);
			int numFlips = state.numFlips + 1;

			if (breadCrumbs.find(childCakes) != breadCrumbs.end()) continue;

			breadCrumbs.insert(childCakes);

			State childState = { childCakes, numFlips };
			q.push(childState);
		}
	}

	return 0;
}

void main()
{
	ifstream fin("pancakes.in");

	if (fin)
	{
		ofstream fout("pancakes.out");;

		string line;
		getline(fin, line);
		
		int n = 0;
		while (line != "0")
		{
			int minFlips = getMinFlips(line);
			fout << minFlips << endl;
			getline(fin, line);
		}

		fin.close();
		fout.close();
	}
}