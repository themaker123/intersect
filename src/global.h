#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include<vector>
#include<set>
#include<cmath>
using namespace std;
class dot {
public:
	double x;
	double y;
	
	bool operator < (const dot& d)const
	{
		if (fabs(d.x - x) < 1e-7 && fabs(d.y - y) < 1e-7) return false;
		else {
			if (d.x > x) return true;
			else if (d.x == x) {
				if (d.y < y) return true;
				else return false;
			}
			else return false;
		}
		
	}
};
// ax+by+c=0
struct line {
	double a;
	double b;
	double c;
};
extern vector<line> lines;
extern set<dot> dots;
extern vector<line> circles;
#endif
