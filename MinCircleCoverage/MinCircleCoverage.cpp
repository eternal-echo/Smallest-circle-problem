// MinCircleCoverage.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

typedef vector<Point> Points;
class Circle
{
public:
	Circle(Point2f c, double r) :center(c), radius(r) {}
	double radius;
	Point2f center;
	friend ostream & operator<<(ostream& output, Circle &c);
};


ostream & operator<<(ostream& output, Circle &c)
{
	output << c.center << "," << c.radius;
	return output;
}
//ay+bx+c=0
class LinearEquation
{
public:
	LinearEquation() {}
	//参数
	LinearEquation(int _a, int _b, int _c) :a(_a), b(_b), c(_c) {}
	//两点式
	LinearEquation(Point A, Point B) {
		a = (A.x - B.x);
		b = -(A.y - B.y);
		c = (A.y*B.x - A.x*B.y);
	}
	//点斜式
	LinearEquation(double _a, double _b, Point A) {
		a = _a;
		b = _b;
		c = -(_a*A.y + _b*A.x);
	}
	double getA() { return a; }
	double getB() { return b; }
	double getC() { return c; }
	double getSlope() { return -b / a; }
	double getIntercept() { return -c / a; }
	friend void Get2LinesIntersection(LinearEquation &l1, LinearEquation &l2, Point2f &intersection);
	friend double distance(Point2f A, Point2f B);
private:
	double a, b, c;
};
//求两线交点
void Get2LinesIntersection(LinearEquation &l1, LinearEquation &l2, Point2f &intersection)
{
	intersection.x = -(l1.a  *l2.c - l2.a*l1.c) / (l1.a*l2.b - l2.a*l1.b);
	intersection.y = (l1.b  *l2.c - l2.b*l1.c) / (l1.a*l2.b - l2.a*l1.b);
}
//求两点距离
double distance(Point2f A, Point2f B)
{
	return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}



//获取三点最小圆覆盖
//方法：中垂线交点（垂心）为外接圆圆心
Circle GetMinCircleOf3Points(vector<Point>  &v3)
{
	Point2f center;
	double radius;
	// two edges of the triangle v1, v2
	LinearEquation l1(v3[0], v3[1]);
	LinearEquation l2(v3[0], v3[2]);

	Point2f midPoint1 = (v3[1] + v3[0]) / 2.0;
	Point2f midPoint2 = (v3[2] + v3[0]) / 2.0;
	LinearEquation midperpendicular1(l1.getB(), -l1.getA(), midPoint1),
		midperpendicular2(l2.getB(), -l2.getA(), midPoint2);
	// center is intersection of midperpendicular lines of the two edges v1, v2
	Get2LinesIntersection(midperpendicular1, midperpendicular2, center);
	radius = distance(center, v3[0]);
	return Circle(center, radius);

}
//获取两点最小圆覆盖
Circle GetMinCircleOf2Points(vector<Point>  &v2)
{
	Point2f center = (v2[0] + v2[1]) / 2;
	double radius = distance(v2[0], v2[1])/2;
	return Circle(center, radius);
}
//点在圆内？
bool isPointInCircle(Circle c, Point2f p)
{
	return distance(p, c.center) < c.radius ? true : false;
}
/*algorithm welzl is
input : Finite sets P and R of points in the plane | R | ≤ 3.
	output : Minimal disk enclosing P with R on the boundary.
	if P is empty or | R | = 3 then
		return trivial(R)
		choose p in P(randomly and uniformly)
		D : = welzl(P −{ p }, R)
		if p is in D then
			return D
			return welzl(P −{ p }, R ∪{ p })*/

Circle welzl(Points P, Points R)
{
	if (R.size() == 3)
	{
		return GetMinCircleOf3Points(R);
	}
	else if (P.empty())
	{
		if (R.size() < 2)
			return Circle(Point2f(0, 0), 0);
		else//R.size=2
			return GetMinCircleOf2Points(R);
	}
	Point p = P.back();//p为最后一个点
	P.pop_back();//P-{p}
	Circle C = welzl(P, R);//递归求解P-p最小圆覆盖 
	if (isPointInCircle(C, p))//若p在P-p的最小覆盖圆内
		return C;
	R.push_back(p);//p在P-p的最小覆盖圆外
	return welzl(P, R);//p为边界点，记录至R中，递归寻找边界点存入R中
}


int main()
{
	srand(time(0));
	Points pts, bound;
	int count = 4, bottom = 400, right = 400, left = 200, top = 200, img_rows = 600, img_cols = 600;
	Mat img(Size(img_rows, img_cols), CV_8UC1);
	img = 0;
	cout << "生成随机点：" << endl;
	int r , c ;
	for (int i=0;i<count;i++)
	{
		r = rand() % (bottom-top)+top;
		c = rand() % (right-left)+left;
		Point p (c, r);
		pts.push_back(p);
		circle(img, p, 2, 255);
		cout << p;
	}
	cout << endl;
	Circle cResult= welzl(pts, bound);
	cout << cResult;
	circle(img, cResult.center, cResult.radius, 255);
	imshow("result", img);
	waitKey();
	return 0;
}
