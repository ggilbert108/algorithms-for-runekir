#include<iostream>
#include<fstream>
#include<bitset>
#include<vector>
#include<set>
using namespace std;

typedef bitset<7> Digit;

set<set<int>> getConfusedDigits(const vector<int>& brokenLeds)
{
	set<set<int>> confused;

	//the numbers passed to the constructor coorospond with the binary matching the LEDs.
	Digit digits[10] 
	{
		Digit(119), Digit(18), Digit(93), Digit(91), Digit(58), Digit(107), Digit(111), Digit(82), Digit(127), Digit(122)
	};

	Digit notBroken;
	notBroken.set();

	for each(int n in brokenLeds)
	{
		notBroken[7 - n].flip();
	}

	for (int i = 0; i < 10; i++)
	{
		digits[i] = digits[i] & notBroken;
	}

	Digit noneOn(0);

	for (int num = 0; num < 10; num++)
	{
		set<int> confusedWithNum;
		confusedWithNum.insert(num);
		for (int j = 0; j < 10; j++)
		{
			if (j == num) continue;

			if ((digits[j] ^ digits[num]) == noneOn)
			{
				confusedWithNum.insert(j);
			}
		}
		if (confusedWithNum.size() > 1)
			confused.insert(confusedWithNum);
	}

	return confused;
}

void main()
{
	ifstream fin("led.in");
	
	if (fin)
	{
		ofstream fout("led.out");

		while (!fin.fail())
		{
			vector<int> brokenLeds;
			
			int num;
			fin >> num;

			if (num == 0)
				break;

			while (num != 0)
			{
				brokenLeds.push_back(num);
				fin >> num;
			}

			set<set<int>> confused = getConfusedDigits(brokenLeds);

			fout << "Case <";

			for (unsigned int i = 0; i < brokenLeds.size(); i++)
			{
				fout << brokenLeds[i];
				if (i != brokenLeds.size() - 1)
					fout << ",";
				else
					fout << ">:";
			}

			string sets = " ";
			for each(set<int> set in confused)
			{
				string setStr = "{";
				for each(int n in set)
				{
					setStr += std::to_string(n);
					setStr += ",";
				}
				setStr = setStr.substr(0, setStr.length() - 1);
				setStr += "}";

				sets += setStr + " ";
			}
			sets = sets.substr(0, sets.length() - 1);

			if (sets != " ")
				fout << sets;
			fout << endl;
		}
		fin.close();
		fout.close();
	}
	else
	{
		cout << "can't find file" << endl;
	}
}