#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

string getDigitCode(char digit)
{
	switch (digit)
	{
	case '0':
		return "nnwwn";
	case '1':
		return "wnnnw";
	case '2':
		return "nwnnw";
	case '3':
		return "wwnnn";
	case '4':
		return "nnwnw";
	case '5':
		return "wnwnn";
	case '6':
		return "nwwnn";
	case '7':
		return "nnnww";
	case '8':
		return "wnnwn";
	case '9':
		return "nwnwn";
	default:
		return "";
	}
}

string getDigitPairCode(char digit1, char digit2)
{
	string barcode = getDigitCode(digit1);
	string spacecode = getDigitCode(digit2);

	string code = "";
	for (int i = 0; i < 5; i++)
	{
		code += toupper(barcode[i]);
		code += spacecode[i];
	}
	
	return code;
}

void main()
{
	ifstream fin("barcode.in");

	if (fin)
	{
		ofstream fout("barcode.out");

		string number;
		fin >> number;

		while (number != "0")
		{
			if (number.length() % 2 != 0)
			{
				number = "0" + number;
			}
			string code = "";
			for (unsigned int i = 0; i < number.length(); i += 2)
			{
				char digit1 = number[i];
				char digit2 =  number[i + 1];

				code += getDigitPairCode(digit1, digit2);
			}

			code = "NnNn" + code + "WnN";
			fout << code << endl;

			fin >> number;
		}

		fin.close();
		fout.close();
	}
	else{
		cout << "file read error" << endl;
	}
}