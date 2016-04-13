#include<iostream>
#include<fstream>
#include<assert.h>
#include<vector>
using namespace std;

#define INF 1000000
#define CW true
#define CCW false
typedef vector<vector<int>> GearBox;

struct GearBoxLocation
{
	int axel, gear;
};

int calculateSpeed(int fromSize, int toSize, int fromSpeed)
{
	//speed is always represented as 3^speed
	if (fromSize == toSize) return fromSpeed;
	if (fromSize < toSize) return fromSpeed - 1;
	return fromSpeed + 1;
}

vector<pair<GearBoxLocation, int>> getAffectedGears(const GearBox& gearBox, const GearBox& gearSpeeds, GearBoxLocation location)
{
	vector<pair<GearBoxLocation, int>> result;

	int gearSize = gearBox[location.axel][location.gear];
	int gearSpeed = gearSpeeds[location.axel][location.gear];

	//get all gears on same axel
	bool reachedMainGear = false;
	for (int i = 0; i < gearBox[0].size(); i++)
	{
		if (i == location.gear)
		{
			reachedMainGear = true;
			continue;
		};
		GearBoxLocation affected = location;
		affected.gear = i;

		if (gearBox[affected.axel][affected.gear] == -1)
		{
			if (!reachedMainGear)
			{
				result.clear();
			}
			else
			{
				break;
			}
		}

		pair<GearBoxLocation, int> pair(affected, gearSpeed);
		result.push_back(pair);
	}

	//check neighboring axels
	if (location.axel > 0)
	{
		int gearAbove = gearBox[location.axel - 1][location.gear];
		if (gearAbove + gearSize == 32)
		{
			int speed = calculateSpeed(gearSize, gearAbove, gearSpeed);
			pair<GearBoxLocation, int> pair({ location.axel - 1, location.gear }, speed);
			result.push_back(pair);
		}
	}
	if (location.axel < gearBox.size() - 1)
	{
		int gearBelow = gearBox[location.axel + 1][location.gear];
		if (gearBelow + gearSize == 32)
		{
			int speed = calculateSpeed(gearSize, gearBelow, gearSpeed);
			pair<GearBoxLocation, int> pair({ location.axel + 1, location.gear }, speed);
			result.push_back(pair);
		}
	}

	return result;
}

bool setGearSpeeds(const GearBox& gearBox, GearBox& gearSpeeds, GearBoxLocation curLocation)
{
	vector<pair<GearBoxLocation, int>> affectedGears = getAffectedGears(gearBox, gearSpeeds, curLocation);

	for each(pair<GearBoxLocation, int> pair in affectedGears)
	{
		GearBoxLocation location = pair.first;
		int speed = pair.second;

		if (gearSpeeds[location.axel][location.gear] != INF)
		{
			if (gearSpeeds[location.axel][location.gear] != speed)
			{
				return false;
			}
			continue;
		}

		gearSpeeds[location.axel][location.gear] = speed;
		setGearSpeeds(gearBox, gearSpeeds, location);
	}
	return true;
}

bool checkAxelConsistency(const GearBox& gearBox, const GearBox& gearSpeeds)
{
	for (int i = 0; i < gearSpeeds.size(); i++)
	{
		int axelSpeed = INF;
		for (int j = 0; j < gearSpeeds[0].size(); j++)
		{
			if (axelSpeed == INF && gearBox[i][j] != -1)
			{
				axelSpeed = gearSpeeds[i][j];
			}
			else if (axelSpeed != gearSpeeds[i][j] && gearBox[i][j] != -1)
			{
				return false;
			}
			if (gearBox[i][j] == -1)
			{
				axelSpeed = INF;
			}
		}
	}
	return true;
}

void printOutputGearSpeed(ofstream& fout, const GearBox& gearBox)
{
	GearBox gearSpeeds(gearBox.size(), vector<int>(gearBox[0].size(), INF));
	vector<int> axelSpeeds(gearBox.size(), INF);
	axelSpeeds[0] = 0;
	
	bool success = true;
	for (int i = 0; i < gearBox[0].size(); i++)
	{
		gearSpeeds[0][i] = 0;
		success = success && setGearSpeeds(gearBox, gearSpeeds, { 0, i });
	}

	if (!success
		|| !checkAxelConsistency(gearBox, gearSpeeds) 
		|| gearSpeeds[gearSpeeds.size() - 1][gearSpeeds[0].size() - 1] == INF)
	{
		fout << "NOT MOVING" << endl;
	}
	else
	{
		int speed = gearSpeeds[gearSpeeds.size() - 1][gearSpeeds[0].size() - 1];
		if (speed < 0)
		{
			fout << "1/";
			speed *= -1;
		}
		speed = pow(3, speed);
		fout << speed << endl;;
	}

	for (int i = 0; i < gearSpeeds.size(); i++)
	{
		for (int j = 0; j < gearSpeeds[0].size(); j++)
		{
			cout << gearSpeeds[i][j] << " ";
		}
		cout << endl;
	}

}

void main()
{
	ifstream fin("gears.in");
	assert(fin);
	ofstream fout("gears.out");

	int numSets;
	fin >> numSets;

	while (numSets-- > 0)
	{
		int gearsPerAxel, numAxels;
		fin >> gearsPerAxel >> numAxels;

		GearBox gearBox(numAxels, vector<int>(gearsPerAxel));

		for (int i = 0; i < numAxels; i++)
		{
			for (int j = 0; j < gearsPerAxel; j++)
			{
				int gearSize;
				fin >> gearSize;
				gearBox[i][j] = gearSize;
			}
		}

		printOutputGearSpeed(fout, gearBox);
	}

	fin.close();
	fout.close();
}