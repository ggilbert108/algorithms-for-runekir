#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define INF 1000000
#define PI 3.14159265358979323846264338

double toRadians(double deg) { return deg * PI / 180; };

/********VECTOR DEFINITION****************************/

struct Vector
{
	double x, y;

	void normalize()
	{
		double len = length();
		x /= len;
		y /= len;
	}

	Vector getNormalizedVector()
	{
		Vector v = { x, y };
		v.normalize();
		return v;
	}

	void rotate(double theta)
	{
		double newX = x * cos(theta) - y * sin(theta);
		double newY = x * sin(theta) + y * cos(theta);
		x = newX;
		y = newY;
	}

	double length()
	{
		return sqrt(x*x + y*y);
	}
};

Vector operator+(Vector& lValue, Vector& rValue)
{
	Vector result = { lValue.x + rValue.x, lValue.y + rValue.y };
	return result;
}

Vector operator-(Vector& lValue, Vector& rValue)
{
	Vector result = { lValue.x - rValue.x, lValue.y - rValue.y };
	return result;
}

Vector operator*(Vector& lValue, double rValue)
{
	Vector result = { lValue.x * rValue, lValue.y * rValue };
	return result;
}

double operator*(Vector& lValue, Vector& rValue)
{
	//computes the dot product of two vectors
	return lValue.x * rValue.x + lValue.y * rValue.y;
}

double angleBetweenVectors(Vector& a, Vector& b)
{
	double result = a * b;
	result /= a.length() * b.length();
	return acos(result);
}

ostream& operator<<(ostream& out, Vector rValue)
{
	out << "(" << rValue.x << ", " << rValue.y << ")";
	return out;
}

/********LINE DEFINITION****************************/

struct Line
{
	Vector p1, p2;

	static bool CCW(Vector& p1, Vector& p2, Vector& point)
	{
		double a = p1.x; double b = p1.y;
		double c = p2.x; double d = p2.y;
		double e = point.x; double f = point.y;
		return (f - b) * (c - a) > (d - b) * (e - a);
	}

	bool intersects(Line& line)
	{
		Vector& p3 = line.p1;
		Vector& p4 = line.p2;
		return CCW(p1, p3, p4) != CCW(p2, p3, p4) && CCW(p1, p2, p3) != CCW(p1, p2, p4);
	}

	double getSlope()
	{
		double dx = p2.x - p1.x;
		double dy = p2.y - p1.y;
		return dy / dx;
	}

	void lengthen(double scale)
	{
		double dx = p2.x - p1.x;
		double dy = p2.y - p1.y;

		p2.x += scale*dx;
		p2.y += scale*dy;
	}

	Vector getIntersection(Line& line)
	{
		double m1 = getSlope();
		double c1 = p1.y - m1 * p1.x;

		double m2 = line.getSlope();
		double c2 = line.p1.y - m2 * line.p1.x;

		double x = (c2 - c1) / (m1 - m2);
		double y = m1 * x + c1;

		Vector result = { x, y };
		return result;
	}

	Vector getVector()
	{
		return p2 - p1;
	}

	Vector getNormalVector(Vector& incoming)
	{
		double dx = p2.x - p1.x;
		double dy = p2.y - p1.y;

		Vector normal1 = {-dy, dx};
		Vector normal2 = { dy, -dx };
		double angle1 = angleBetweenVectors(normal1, incoming);
		double angle2 = angleBetweenVectors(normal2, incoming);

		return normal1;
		//return (angle1 < angle2) ? normal1 : normal2;
	}

	Vector getReflection(Vector& incoming)
	{
		Vector n = getNormalVector(incoming);
		n.normalize();
		double scalar = 2 * (incoming * n);
		Vector result = n * scalar;
		result = incoming - result;

		return result;;
	}

	double length()
	{
		Vector v = p2 - p1;
		return v.length();
	}

	double distanceToPoint(Vector& point)
	{
		double len = length();

		if (len == 0.0)
		{
			Vector v = point - p1;
			return v.length();
		}
		Vector pv = point - p1;
		Vector wv = p2 - p1;
		
		double t = pv * wv;
		t /= len * len;
		if (t < 0.0)
			return pv.length();
		if (t > 1.0)
		{
			Vector pw = point - p1;
			return pw.length();
		}

		Vector projection = p1 + (wv * t);
		Vector pp = projection - point;
		return pp.length();
	}
};

/********MAIN CODE****************************/

bool getClosestMirror(vector<Line>& mirrors, Line line, Line& result)
{
	double minDist = INF;
	Line bestMirror = { { 0, 0 }, { 0, 0 } };
	Vector compare = line.p1;
	for (int i = 0; i < mirrors.size(); i++)
	{
		Line mirror = mirrors[i];
		if (line.intersects(mirror))
		{
			Vector intersectionPoint = line.getIntersection(mirror);
			Vector fromCompare = intersectionPoint - compare;

			double dist = fromCompare.length();
			if (dist < minDist && dist > 0.1)
			{
				minDist = dist;
				bestMirror = mirror;
			}
		}
	}

	if (minDist < INF)
	{
		result = bestMirror;
		return true;
	}
	return false;
}


bool isDangerAngle(vector<Line>& mirrors, double angle)
{
	Vector laser = { 1, 0 };
	laser.rotate(toRadians(angle));

	Line laserLine = { { 0, 0 }, laser };
	laserLine.lengthen(10000);

	vector<Line> lasers;
	lasers.push_back(laserLine);

	for (int i = 0; i < 7; i++)
	{
		Line bestMirror;
		if (getClosestMirror(mirrors, laserLine, bestMirror))
		{
			Vector reflect = bestMirror.getReflection(laser);
			laser = reflect;
			Vector p1 = bestMirror.getIntersection(laserLine);
			Vector p2 = p1 + laser;
			laserLine = { p1, p2 };
			laserLine.lengthen(10000);
			lasers.push_back(laserLine);;
		}
		else
		{
			break;
		}
	}

	Vector center{ 0, 0 };
	for (int i = 1; i < lasers.size(); i++)
	{
		Line l = lasers[i];
		double distance = l.distanceToPoint(center);
		if (distance < 0.01)
			return true;
	}

	return false;
}

void main()
{
	fstream fin("laser.in");
	if (fin)
	{
		fstream fout("laser.out");

		int numMirrors;
		fin >> numMirrors;
		while (numMirrors > 0)
		{
			vector<Line> mirrors;

			for (int i = 0; i < numMirrors; i++)
			{
				double x1, y1, x2, y2;
				fin >> x1 >> y1 >> x2 >> y2;
				if (abs(x1 - x2) < .1) x2 += .0000001; // to avoid infinte slope

				Line mirror{ { x1, y1 }, { x2, y2 } };
				mirrors.push_back(mirror);
			}

			set<int> result;
			for (int theta = 0; theta < 360; theta++)
			{
				for (double eps = -.5; eps < .5; eps += 0.0001)
				{
					if (isDangerAngle(mirrors, theta + eps))
					{
						result.insert(theta);
						break;
					}
				}
			}
			string resultStr = "";
			for each(int n in result)
			{
				resultStr += to_string(n) + " ";
			}
			if (resultStr == "")
			{
				resultStr = "no danger";
			}
			cout << resultStr << endl;
			fin >> numMirrors;
		}
		fin.close();
		fout.close();
	}
}