#pragma once

struct point
{
	double x;
	double y;
	point() { x = 0; y = 0; }
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
	//int num;
public:
	line() {}
	line(point l, point r) : left(l), right(r) 
	{
		if (r < l) { left = r; right = l; }
	};
	line(double x1, double y1, double x2, double y2) : left(x1, y1), right(x2, y2) 
	{
		if (right < left)
		{
			right = left;
			left.x = x2;
			left.y = y2;
		}
	};
	point getLeft() { return left; }
	point getRight() { return right; }
	//int getNum() { return num; }
	void set(double x1, double y1, double x2, double y2) 
	{ 
		left.x = x1; left.y = y1; 
		right.x = x2; right.y = y2; 
		if (right < left)
		{
			right = left;
			left.x = x2;
			left.y = y2;
		}
	}
	void set(point l, point r) 
	{ 
		if (l < r)
		{
			left = l; right = r;
		}
		else
		{
			left = r; right = l;
		}
	}
	bool intersect(line t)
	{
		//double t1, t2;
		//double dx1 = right.x - left.x, dy1 = right.y - left.y;
		//double dx2 = t.left.x - t.right.x, dy2 = t.left.y - t.right.y;
		//double dx = t.left.x - left.x, dy = t.left.y - left.y;

		//if (dx1 * dy2 == dy1 * dx2) return false;

		//t2 = (dy - dx * dy1 / dx1) / (dy2 - dx2 * dy1 / dx1);

		//double x = t.left.x - t2 * dx2;

		//if (t2 > -1e-19 && t.left.x <= x && x <= t.right.x) return true;

		double  v1x = right.x - left.x, v1y = right.y - left.y,

			v2x = t.right.x - left.x, v2y = t.right.y - left.y,

			v3x = t.left.x - left.x, v3y = t.left.y - left.y,

			v4x = t.right.x - t.left.x, v4y = t.right.y - t.left.y,

			v5x = right.x - t.left.x, v5y = right.y - t.left.y,

			v6x = left.x - t.left.x, v6y = left.y - t.left.y;

		bool b1 = false, b2 = false;

		double d1 = v1x * v2y - v1y * v2x,
			d2 = v1x * v3y - v1y * v3x;

		if (d1 == 0 && d2 == 0)
			if (v2x >= 0 && v5x >= 0)
				return true;
			else
				return false;

		double d = d1 * d2;

		if (d < 0 || d1 == 0 && v2x < v1x || d2 == 0 && v3x < v1x) b1 = true;

		d1 = v4x * v5y - v4y * v5x;
		d2 = v4x * v6y - v4y * v6x;

		d = d1 * d2;

		if (d < 0 || d1 == 0 && v5x < v4x || d2 == 0 && v6x < v4x) b2 = true;

		return b1 && b2;
	}
};

struct CntPoint
{
	point pt;
	int ln;
	CntPoint() { ln = -1; }
	CntPoint(point _pt, int _ln) : pt(_pt), ln(_ln) {}
	bool operator==(const CntPoint p) const
	{
		return pt.y == p.pt.y && ln == p.ln;
	}
	bool operator!=(const CntPoint p) const
	{
		return pt.y != p.pt.y || ln != p.ln;
	}
	bool operator>(const CntPoint p) const
	{
		return pt.y > p.pt.y || pt.y == p.pt.y && ln > p.ln;
	}
	bool operator>=(const CntPoint p) const
	{
		return pt.y >= p.pt.y || pt.y == p.pt.y && ln >= p.ln;
	}
	bool operator<(const CntPoint p) const
	{
		return pt.y < p.pt.y || pt.y == p.pt.y && ln < p.ln;
	}
	bool operator<=(const CntPoint p) const
	{
		return pt.y <= p.pt.y || pt.y == p.pt.y && ln <= p.ln;
	}
};
