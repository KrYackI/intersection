#pragma once

struct point
{
	double x;
	double y;
	point(double _x, double _y) : x(_x), y(_y) {};
	bool operator<(const point& r)
	{
		if (x < r.x || x == r.x && y < r.y) return true;
		return false;
	}
	bool operator==(const point& r)
	{
		if (x == r.x && y == r.y) return true;
		return false;
	}
};

class line
{
	point left;
	point right;
public:
	line(point l, point r) : left(l), right(r) {}; 
	line(double x1, double y1, double x2, double y2) : left(x1, y1), right(x2, y2) {};
	bool intersect(line t)
	{
		double t1, t2;
		double dx1 = right.x - left.x, dy1 = right.y - left.y;
		double dx2 = t.left.x - t.right.x, dy2 = t.left.y - t.right.y;
		double dx = t.left.x - left.x, dy = t.left.y - left.y;

		if (dx1 * dy2 == dy1 * dx2) return false;

		t2 = (dy - dx * dy1 / dx1) / (dy2 - dx2 * dy1 / dx1);

		double x = t.left.x - t2 * dx2;

		if (t.left.x <= x && x <= t.right.x) return true;
		return false;
	}
};