#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

typedef map<char, set<char>> CharMap;

void findIncompatibles(CharMap& incompatible, char a, char b)
{
	if (incompatible.find(a) == incompatible.end())
	{
		set<char> charSet;
		incompatible.insert(pair < char, set<char>>(a, charSet));
	}
	if (incompatible.find(b) == incompatible.end())
	{
		set<char> charSet;
		incompatible.insert(pair < char, set<char>>(b, charSet));
	}

	incompatible[a].insert(b);
	incompatible[b].insert(a);
}

void findIncompatibles(CharMap& incompatible, string word)
{
	for (int i = 0; i < word.length(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			findIncompatibles(incompatible, word[i], word[j]);
		}
	}
}

bool areCompatible(CharMap& incompatible, char a, char b)
{
	if (a == b) return true;
	return incompatible[a].find(b) == incompatible[a].end();
}

bool areCompatible(CharMap& incompatible, string str, char ch)
{
	for (int i = 0; i < str.length(); i++)
	{
		char strCh = str[i];
		if (!areCompatible(incompatible, strCh, ch))
		{
			return false;
		}
	}
	return true;
}

vector<string> getCubes(CharMap& incompatible, vector<string> cubes, string allChars, int pos)
{
	if (pos >= allChars.length())
	{
		return cubes;
	}
	
	char ch = allChars[pos];

	for (int i = 0; i < cubes.size(); i++)
	{
		if (cubes[i].length() < 6 && areCompatible(incompatible, cubes[i], ch))
		{
			cubes[i] += ch;
			vector<string> result = getCubes(incompatible, cubes, allChars, pos + 1);
			if (result.size() > 0)
			{
				return result;
			}
			cubes[i] = cubes[i].substr(0, cubes[i].length() - 1);
		}
	}
	vector<string> empty;
	return empty;
}

void main()
{
	ifstream fin("cubes.in");
	assert(fin);

	ofstream fout("cubes.out");

	int numWords;
	char extra;
	fin >> numWords >> extra;

	while (numWords > 0)
	{
		int numCubes = -1;
		CharMap incompatible;
		for (int i = 0; i < numWords; i++)
		{
			string word;
			fin >> word;
			if (numCubes == -1) numCubes = word.length();
			findIncompatibles(incompatible, word);
		}

		string allChars = "";
		for each(pair <char, set<char>> pair in incompatible)
		{
			allChars += pair.first;
		}
		vector<string> cubes(numCubes);
		vector<string> result = getCubes(incompatible, cubes, allChars, 0);

		for (int i = 0; i < result.size(); i++)
		{
			if (result[i].length() < 6)
				result[i] += extra;
			sort(result[i].begin(), result[i].end());
		}

		sort(result.begin(), result.end());

		string resLine = "";
		for each(string str in result)
		{
			resLine += str + " ";
		}
		resLine = resLine.substr(0, resLine.length() - 1);
		fout << resLine << endl;
		fin >> numWords >> extra;
	}

	fin.close();
	fout.close();
}