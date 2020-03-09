#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<cmath>
#include<fstream>
#include"global.h"
using namespace std;
vector<line> lines;
vector<line> circles;
set<dot> dots;
ifstream in;
ofstream out;
void trans(line &l,int x1,int y1,int x2,int y2) {
	int a, b, c;
	a = y1 - y2;
	b = x2 - x1;
	c = x1 * y2 - x2 * y1;
	l.a = a;
	l.b = b;
	l.c = c;
}
int calaIntersectLineOnly(line l0,line l1){
	double  k;
	dot d;
	k = l0.a * l1.b - l0.b * l1.a;
	if (k == 0) return -1;//平行没有交点
	d.x = (l0.b * l1.c - l0.c * l1.b) / k;
	d.y = (l1.a * l0.c - l1.c * l0.a) / k;
	dots.insert(d);
	return 0;
}
int calaIntersectLineCircle(line l, line circle) {
	double  a = 0, c = 0, r = 0 ;
	dot d1, d2;
	a = circle.a;
	c = circle.b;
	r = circle.c;
	//如果斜率不存在
	if (l.b == 0) {
		double t;
		t= -1 * l.c / l.a;
		double delt;
		delt = r * r - a * a - (l.c * l.c + 2 * l.c * a * l.a) / (l.a * l.a);
		if (delt < 0) return -1;
		double t1;
		t1= sqrt(delt);
		d1.x = t;
		d1.y = c + t1;
		dots.insert(d1);
		if (delt == 0) return 0;
		d2.x = t;
		d2.y = c - t1;
		dots.insert(d2);
	}
	else {
		double b_2 = l.b * l.b;
		double a2 = b_2+l.a*l.a;
		double b2 = -2*b_2*a + 2 * l.a * (l.c + l.b * c);
		double c2 = a*a*b_2 + (l.c + l.b * c) * (l.c + l.b * c) - r*r*b_2;
		double delt2;
		delt2 = b2 * b2 - 4 * a2 * c2;
		if (delt2 < 0) return -1;
		double delt;
		delt = sqrt(delt2);
		d1.x = (-1 * b2 + delt) / (2 * a2);
		d1.y = (-l.a * d1.x - l.c) / l.b;
		dots.insert(d1);
		if (delt == 0) return 0;
		d2.x = (-1 * b2 - delt) / (2 * a2);
		d2.y = (-l.a * d2.x - l.c) / l.b;
		dots.insert(d2);
	}
	return 0;
}
int calaIntersectCircleOnly(line c1, line c2) {
	double a1 = c1.a, b1 = c1.b, r1 = c1.c;
	double a2 = c2.a, b2 = c2.b, r2 = c2.c;
	double a, b, c;
	a = 2 * (a2 - a1);
	b = 2 * (b2 - b1);
	c = a1 * a1 + b1 * b1 - a2 * a2 - b2 * b2 + r2 * r2 - r1 * r1;
	//得到两圆的交线;
	line l;
	l.a = a;
	l.b = b;
	l.c = c;
	if (a == 0 && b == 0) return -1;
	//if ((a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2) - (r1-r2)*(r1-r2) < 0) return -1;
	calaIntersectLineCircle(l,c1);
	return 0;
}
void lineOnly() {
	int size = lines.size();
	int j = 0;;
	line l0, l1;
	for (int i = 0; i < size; i++) {
		l0 = lines.at(i);
		for (j = 0; j < i; j++) {
			l1 = lines.at(j);
			calaIntersectLineOnly(l0, l1);
		}
	}
}
void lineAndCircle() {
	int lineSize = lines.size();
	int circleSize = circles.size();
	line l, circle;
	int j;
	for (int i = 0; i < circleSize; i++) {
		circle = circles.at(i);
		for (j = 0; j < lineSize; j++) {
			l = lines.at(j);
			calaIntersectLineCircle(l,circle);
		}
	}
}
void circleOnly() {
	int size = circles.size();
	int j = 0;
	line l0, l1;
	for (int i = 0; i < size; i++) {
		l0 = circles.at(i);
		for (j = 0; j < i; j++) {
			l1 = circles.at(j);
			calaIntersectCircleOnly(l0, l1);
		}
	}
}
void inputModule() {
	int n, x1, y1, x2, y2;
	int x, y, r;
	char type;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> type;
		if (type == 'L') {
			cin >> x1 >> y1 >> x2 >> y2;
			line l;
			//将坐标表示的直线转化为 ax+by+c=0的一般表示
			trans(l, x1, y1, x2, y2);
			lines.push_back(l);
		}
		else if (type == 'C') {
			cin >> x >> y >> r;
			line cir;
			cir.a = x;
			cir.b = y;
			cir.c = r;
			circles.push_back(cir);
		}
	}
}
void input(int argc,char *argv[]) {
	int n, x1, y1, x2, y2;
	int x, y, r;
	char type;

	string inputPath;
	string outputPath;
	if (argc != 5) exit(0);
	if (strcmp(argv[1], "-i") == 0) {
		inputPath = string(argv[2]);
		outputPath = string(argv[4]);
	}
	else {
		inputPath = string(argv[4]);
		outputPath = string(argv[2]);
	}
	in.open(inputPath, ios::in);
	out.open(outputPath, ios::out);
	in >> n;
	for (int i = 0; i < n; i++) {
		in >> type;
		if (type == 'L') {
			in >> x1 >> y1 >> x2 >> y2;
			line l;
			//将坐标表示的直线转化为 ax+by+c=0的一般表示
			trans(l, x1, y1, x2, y2);
			lines.push_back(l);
		}
		else if (type == 'C') {
			in >> x >> y >> r;
			line cir;
			cir.a = x;
			cir.b = y;
			cir.c = r;
			circles.push_back(cir);
		}
	}
}
int main(int argc, char* argv[]) {
	input(argc, argv);
	//inputModule();
	lineOnly();
	lineAndCircle();
	circleOnly();
	cout << dots.size() << endl;
	out << dots.size() << endl;
}