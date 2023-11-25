#pragma once

#include <iostream>
#include "line.h"


line* generate1(int n)
{
	line* arr = new line[n];
	for (int i = 0; i < n; ++i)
		arr[i].set((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX);
	return arr;
}

line* generate1(int n, int k)
{
	line* arr = new line[n];
	for (int i = 0; i < k; ++i)
	{
		double x0 = (double)rand() / RAND_MAX;
		double x1 = x0 + (double)rand() / RAND_MAX * (1 - x0);
		arr[i].set(x0, (double)i / n, x1, (double)i / n);
	}
	double x0 = (double)rand() / RAND_MAX;
	double x1 = x0 + (double)rand() / RAND_MAX * (1 - x0);
	double x2 = x0 + (double)rand() / RAND_MAX * (x1 - x0);
	double x3 = x2 + (double)rand() / RAND_MAX * (x1 - x2);
	arr[k].set(x0, (double)(k + 1) / n, x1, (double)k / n);
	arr[k + 1].set(x2, (double)k / n, x3, (double)(k + 1) / n);
	for (int i = k + 2; i < n; ++i)
	{
		double x0 = (double)rand() / RAND_MAX;
		double x1 = x0 + (double)rand() / RAND_MAX * (1 - x0);
		arr[i].set(x0, (double)i / n, x1, (double)i / n);
	}
	return arr;
}

line* generate2(int n, double r)
{
	line* arr = new line[n];
	r = r / 2;
	for (int i = 0; i < n; ++i)
	{
		point o((double)rand() / RAND_MAX, (double)rand() / RAND_MAX);
		double sin = (double)rand() / RAND_MAX * 2 - 1;
		double cos = sqrt(1 - sin * sin);
		arr[i].set(o.x - r * cos, o.y - r * sin, o.x + r * cos, o.y + r * sin);
	}
	return arr;
}

line* generate2(int n, double r, int k)
{
	line* arr = new line[n];
	for (int i = 0; i < k; ++i)
	{
		double x0 = (double)rand() / RAND_MAX;
		arr[i].set(x0, (double)i / n, x0 + r, (double)i / n);
	}
	double x0 = (double)rand() / RAND_MAX;
	double x1 = x0 + r * (2 * r * r * n * n - 1) / 2 * r * r * n * n;
	double x2 = x0 + (double)rand() / RAND_MAX * (x1 - x0);
	double x3 = x2 + r * (2 * r * r * n * n - 1) / 2 * r * r * n * n;
	arr[k].set(x0, (double)(k + 1) / n, x1, (double)k / n);
	arr[k + 1].set(x2, (double)k / n, x3, (double)(k + 1) / n);
	for (int i = k + 2; i < n; ++i)
	{
		double x0 = (double)rand() / RAND_MAX;
		arr[i].set(x0, (double)i / n, x0 + r, (double)i / n);
	}
	return arr;
}

line* enter(istream& in, int& n)
{
	in >> n;
	line* arr = new line[n];
	double x1, y1, x2, y2;
	for (int i = 0; i < n; ++i)
	{
		in >> x1 >> y1 >> x2 >> y2;
		arr[i].set(x1, y1, x2, y2);
	}
	return arr;
}

//line* enter(ifstream& in)
//{
//	int n;
//	in >> n;
//	line* arr = new line[n];
//	double x1, y1, x2, y2;
//	for (int i = 0; i < n; ++i)
//	{
//		in >> x1 >> y1 >> x2 >> y2;
//		arr[i].set(x1, y1, x2, y2);
//	}
//	return arr;
//}