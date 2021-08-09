# Smallest-circle-problem
# 最小圆覆盖经典算法
<font color=#999AAA >提示：这里可以添加系列文章的所有文章的目录，目录需要自己手动添加
例如：第一章 Python 机器学习入门之pandas的使用
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">


<font color=#999AAA >提示：写完文章后，目录可以自动生成，如何生成可参考右边的帮助文档

@[TOC](文章目录)

</font>

<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

# 前言

<font color=#999AAA >参考文献：
https://en.wikipedia.org/wiki/Smallest-circle_problem
维基百科上关于最小圆覆盖有很全面的论述（需要科学上网）</font>
https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%9C%86%E8%A6%86%E7%9B%96%E7%AE%97%E6%B3%95/22799983
百度也有
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">

<font color=#999AAA >提示：以下是本篇文章正文内容，下面案例可供参考

# 一、原文

![在这里插入图片描述](https://img-blog.csdnimg.cn/72b867a180f04f789c93a272efcf1b44.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
Welzl的算法
该算法是递归的，并且将两个（有限的）点P和R作为参数;它计算P和R联合的最小包围圆，只要R的每个点都是最终最小包围圆的边界点之一。因此，原始的最小包围圆问题可以通过调用算法来解决，其中P等于要封闭的点集合，R等于空集合;当算法递归调用自身时，它将放大传递给递归调用的集合R，直到它包含圆的所有边界点。
　　该算法以随机顺序处理P的点，保持处理点的集合S和包含并集S∪R的最小圆D.在每一步，它测试下一个要处理的点p是否是在D;如果不是，该算法用集合S和R∪p上的算法的递归调用的结果替换D.无论圆是否被替换，p都被包括在集合S中。因此，处理每个点包括在恒定时间内测试该点是否属于单个圆并且可能执行对算法的递归调用。可以看出，总时间是线性的。

```python
algorithm welzl:
    input: Finite sets P and R of points in the plane
    output: Minimal disk enclosing P with R on the boundary, or undefined if no such disk exists
    if P is empty or |R| ≥ 3:
        if |R| = 1:
            (we do this to support multisets with duplicate points)
            (we assume that a circle with a radius of zero can exist)
            p := R[0]
            return circle(p, 0)
        else if |R| = 2:
            (we do this to support multisets with duplicate points)
            (we use that the smallest circle between two points has a center at their midpoint)
            (and the segment that passes through them is a diameter of the circle)
            p0 := R[0]
            p1 := R[1]
            center := midpoint(p0, p1)
            diameter := distance(p0, p1)
            return circle(center, diameter / 2)
        else if the points of R are cocircular:
            return the ball they determine
        else:
            return undefined
  

 choose p in P (randomly and uniformly)
           D := welzl(P - { p }, R)
           if p is in D:
               return D
           return welzl(P - { p }, R ∪ { p })
```
    

The algorithm is recursive.

The initial input is a set P of points. The algorithm selects one point p randomly and uniformly from P, and recursively finds the minimal circle containing P – {p}, i.e. all of the other points in P except p. If the returned circle also encloses p, it is the minimal circle for the whole of P and is returned.

Otherwise, point p must lie on the boundary of the result circle. It recurses, but with the set R of points known to be on the boundary as an additional parameter.

The recursion terminates when P is empty, and a solution can be found from the points in R: for 0 or 1 points the solution is trivial, for 2 points the minimal circle has its center at the midpoint between the two points, and for 3 points the circle is the circumcircle of the triangle described by the points. (In three dimensions, 4 points require the calculation of the circumsphere of a tetrahedron.)

Recursion can also terminate when R has size 3 (in 2D, or 4 in 3D) because the remaining points in P must lie within the circle described by R.
![在这里插入图片描述](https://img-blog.csdnimg.cn/b10daf1bf4fe4f49a62512aa8d0804c7.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
Welzl's paper states that it is sufficient to randomly permute the input at the start, rather than performing independently random choices of p on each recursion.

It also states that performance is improved by dynamically re-ordering the points so that those that are found to be outside a circle are subsequently considered earlier, but this requires a change in the structure of the algorithm to store P as a "global".





# 二、算法实现
## 1.算法基本流程
![在这里插入图片描述](https://img-blog.csdnimg.cn/fb4b78a4108847cf8360864aa298fabf.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/6c0bfbb0cd2941c9ac81e3e0fd9b6cd6.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzMDA2Mjk0,size_16,color_FFFFFF,t_70)
最后，Welzl指出通过动态重新排序点可以提高性能，以便随后更早地考虑那些被发现在圆外的点。



## 2.代码

<font color=#999AAA >代码如下：



```c
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
	return welzl(P, R);//p为边界点，记录至R中，递归寻找边界点存入R
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
```



其中Circle welzl(Points P, Points R)为核心函数，参数P为输入点集，参数N为边界点集，及位于最小覆盖圆上的点，可能为两个或者三个。
其中N是边界点集，一定位于最小圆上，N为求解最小圆的关键，通过上述递归求出。
P为输入点集，每递归一次就减一个。
最终N有3个或者P为空递归停止。
情况1：N为3。说明边界点已经找完了。
情况2：P为空。N为2不一定找完，可能还有一个点，所以得通过递归遍历所有剩余点，如果所有点都在这个2个边界点构成圆里面（就是以两边界点为直径的圆），也就是P为空（所有点都遍历了一遍），则递归也可以结束。
<hr style=" border:solid; width:100px; height:1px;" color=#000000 size=1">




# 总结
<font color=#999AAA >
本人也在学习中，疏忽之处在所难免，有错误欢迎指出。

