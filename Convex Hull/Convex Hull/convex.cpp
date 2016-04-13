#include<iostream>
#include<fstream>
#include<set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Point
{
	float x, y;

	bool operator<(const Point& rValue) const
	{
		if (abs(x - rValue.x) < 0.01)
		{
			return y < rValue.y;
		}
		return x < rValue.x;
	}
};

bool operator==(const Point& lValue, const Point& rValue)
{
	return abs(lValue.x - rValue.x) < 0.1 && abs(lValue.y - rValue.y) < 0.1;
}

bool ccw(Point endpointA, Point endpointB, Point point)
{
	double a = endpointA.x; double b = endpointA.y;
	double c = endpointB.x; double d = endpointB.y;
	double e = point.x;		double f = point.y;
	return (f - b) * (c - a) >= (d - b) * (e - a);	
}

Point getPoint(set<Point>& points, vector<Point> hull)
{
	for each(Point point in points)
	{
		if (find(hull.begin(), hull.end(), point) != hull.end())
		{
			return point;
		}
	}
	return *points.begin();
}

bool areColinear(set<Point>& points)
{
	Point a = *points.begin();
	Point b = *(++points.begin());

	double dx = b.x - a.x;
	double dy = b.y - a.y;
	if (dx == 0)
	{
		dx += .000001;
	}
	double m = dy / dx;
	double c = a.y - m * a.x;

	for each(Point point1 in points)
	{
		for each(Point point2 in points)
		{
			if (point1 == point2) continue;

			dx = point2.x - point1.x;
			dy = point2.y - point1.y;
			if (dx == 0)
			{
				dx += .000001;
			}
			double pm = dy / dx;
			double pc = a.y - m * a.x;
			
			if (!(abs(pm - m) < 0.01 && abs(pc - c) < 0.01))
			{
				return false;
			}
		}
	}

	return true;
}

vector<Point> getConvexHull(set<Point>& points)
{
	vector<Point> hull;

	if (areColinear(points))
	{
		Point leftMost = *points.begin();
		Point rightMost = *(--points.end());

		hull.push_back(leftMost);
		hull.push_back(rightMost);
		return hull;
	}

	Point leftMost{10000, 10000};
	for each(Point point in points)
	{
		if (point.x < leftMost.x)
		{
			leftMost = point;
		}
		else if (abs(point.x - leftMost.x) < 0.001)
		{
			if (point.y < leftMost.y)
			{
				leftMost = point;
			}
		}
	}

	Point pointOnHull = leftMost;
	Point endPoint = { 100000, 100000 };
	while (!(endPoint == leftMost))
	{
		hull.push_back(pointOnHull);
		endPoint = *points.begin();
		for each(Point point in points)
		{
			if (point == endPoint || point == pointOnHull) continue;
			if (endPoint == pointOnHull || ccw(pointOnHull, endPoint, point))
			{
				endPoint = point;
			}
		}
		pointOnHull = endPoint;
		points.erase(pointOnHull);
	}
	
	return hull;
}

void main()
{
	ifstream fin("convex.in");

	if (fin)
	{
		ofstream fout("convex.out");

		int numPoints;
		fin >> numPoints;

		int setNumber = 1;

		while (numPoints != 0)
		{
			set<Point> points;
			for (int i = 0; i < numPoints; i++)
			{
				float x, y;
				fin >> x >> y;
				points.insert({ x, y });
			}

			vector<Point> hull = getConvexHull(points);

			fout << "Set #" << setNumber++ << ": ";
			for each(Point point in hull)
			{
				fout << "(" << point.x << "," << point.y << ") ";
			}
			fout << endl;

			fin >> numPoints;
		}

		fin.close();
		fout.close();
	}
	else
	{
		cout << "cannout find file" << endl;
	}
}