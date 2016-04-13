#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

typedef vector<string> Statement;

bool isVariable(Statement& statement, int& curWordIndex)
{
	string terminals = "xyz";
	string curWord = statement[curWordIndex];

	return (terminals.find(curWord) != string::npos);
}

bool isOperator(Statement& statement, int& curWordIndex)
{
	string terminals = "+=";
	string curWord = statement[curWordIndex];

	return (terminals.find(curWord) != string::npos);
}

bool isNumber(Statement& statement, int& curWordIndex)
{
	string terminals = "0123456789";
	string curWord = statement[curWordIndex];

	return (terminals.find(curWord) != string::npos);
}

bool isTerm(Statement& statement, int& curWordIndex)
{
	return isNumber(statement, curWordIndex) || isVariable(statement, curWordIndex);
}

bool isExpression(Statement& statement, int& curWordIndex)
{
	int savePos = curWordIndex;
	if (isTerm(statement, curWordIndex))
	{
		return true;
	}
}

void main()
{

}