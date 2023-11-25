#pragma once
#include "2,3-tree.h"
#include "AVL_tree.h"
#include "line.h"
#include <Algorithm>
#include <math.h>

using namespace std;



bool f(pair<point, int> a, pair<point, int> b)
{
	return a.first < b.first;
}

template <class container>
bool func(line* arr, int n, int& s1, int& s2)
{
	pair<point, int>* pointArr = new pair<point, int>[2 * n];
	for (int i = 0; i < n; ++i)
	{
		pointArr[2 * i].first = arr[i].getLeft();
		pointArr[2 * i].second = i;
		pointArr[2 * i + 1].first = arr[i].getRight();
		pointArr[2 * i + 1].second = i;
	}

	sort(pointArr, pointArr + 2 * n, f);

	container cont;

	for (int i = 0; i < 2 * n; ++i)
	{
		point p = pointArr[i].first;
		int l = pointArr[i].second;
		CntPoint cpt(p, l);
		if (p == arr[l].getLeft())
		{
			cont.insert(cpt);
			if (cont.getPrev(cpt))
			{
				int l1 = cont.getPrevItem(cpt).ln;
				if (arr[l1].intersect(arr[l]))
				{
					s1 = l1;
					s2 = l;
					delete[] pointArr;
					return true;
				}
			}
			if (cont.getNext(cpt))
			{
				int l2 = cont.getNextItem(cpt).ln;
				if (arr[l2].intersect(arr[l]))
				{
					s1 = l;
					s2 = l2;
					delete[] pointArr;
					return true;
				}
			}
		}
		else
		{
			if (cont.getNext(cpt) && cont.getPrev(cpt))
			{
				int l1 = cont.getPrevItem(cpt).ln;
				int l2 = cont.getNextItem(cpt).ln;
				if (arr[l1].intersect(arr[l2]))
				{
					s1 = l1;
					s2 = l2;
					delete[] pointArr;
					return true;
				}
			}
			cont.remove(cpt);
		}
	}
	delete[] pointArr;
	return false;
}

bool funcAVL(line* arr, int n, int& s1, int& s2, int& h)
{
	pair<point, int>* pointArr = new pair<point, int>[2 * n];
	for (int i = 0; i < n; ++i)
	{
		pointArr[2 * i].first = arr[i].getLeft();
		pointArr[2 * i].second = i;
		pointArr[2 * i + 1].first = arr[i].getRight();
		pointArr[2 * i + 1].second = i;
	}

	sort(pointArr, pointArr + 2 * n, f);

	AVLtree<CntPoint> cont;
	int curh = 0;

	for (int i = 0; i < 2 * n; ++i)
	{
		point p = pointArr[i].first;
		int l = pointArr[i].second;
		CntPoint cpt(arr[l].getLeft(), l);
		auto nodel = cont.getPrev(cpt);
		auto noder = cont.getNext(cpt);
		if (p == arr[l].getLeft())
		{
			cont.insert(cpt);
			curh = cont.getHeight();
			if (curh > h)
				h = curh;
			if (nodel)
			{
				int l1 = nodel->value.ln;
				if (arr[l1].intersect(arr[l]))
				{
					s1 = l1;
					s2 = l;
					delete[] pointArr;
					return true;
				}
			}
			if (noder)
			{
				int l2 = noder->value.ln;
				if (arr[l2].intersect(arr[l]))
				{
					s1 = l;
					s2 = l2;
					delete[] pointArr;
					return true;
				}
			}
		}
		else
		{
			if (nodel && noder)
			{
				int l1 = nodel->value.ln;
				int l2 = noder->value.ln;
				if (arr[l1].intersect(arr[l2]))
				{
					s1 = l1;
					s2 = l2;
					delete[] pointArr;
					return true;
				}
			}
			cont.remove(cpt);
		}
	}
	delete[] pointArr;
	return false;
}


bool func23(line* arr, int n, int& s1, int& s2, int& h)
{
	pair<point, int>* pointArr = new pair<point, int>[2 * n];
	for (int i = 0; i < n; ++i)
	{
		pointArr[2 * i].first = arr[i].getLeft();
		pointArr[2 * i].second = i;
		pointArr[2 * i + 1].first = arr[i].getRight();
		pointArr[2 * i + 1].second = i;
	}

	sort(pointArr, pointArr + 2 * n, f);

	tree_23<CntPoint> cont;
	int curh = 0;

	for (int i = 0; i < 2 * n; ++i)
	{
		point p = pointArr[i].first;
		int l = pointArr[i].second;
		CntPoint cpt(arr[l].getLeft(), l);
		if (p == arr[l].getLeft())
		{
			cont.insert(cpt);
			int nl;
			auto nodel = cont.getPrev(nl, cpt);
			int nr;
			auto noder = cont.getNext(nr, cpt);
			curh = cont.getHeight();
			if (curh > h)
				h = curh;
			if (nodel != nullptr)
			{
				int l1 = nodel->value[nl].ln;
				if (arr[l1].intersect(arr[l]))
				{
					s1 = l1;
					s2 = l;
					delete[] pointArr;
					return true;
				}
			}
			if (noder != nullptr)
			{
				int l2 = noder->value[nr].ln;
				if (arr[l2].intersect(arr[l]))
				{
					s1 = l;
					s2 = l2;
					delete[] pointArr;
					return true;
				}
			}
		}
		else
		{
			int nl;
			auto nodel = cont.getPrev(nl, cpt);
			int nr;
			auto noder = cont.getNext(nr, cpt);
			if (nodel != nullptr && noder != nullptr)
			{
				int l1 = nodel->value[nl].ln;
				int l2 = noder->value[nr].ln;
				if (arr[l1].intersect(arr[l2]))
				{
					s1 = l1;
					s2 = l2;
					delete[] pointArr;
					return true;
				}
			}
			cont.remove(cpt);
		}
	}
	delete[] pointArr;
	return false;
}


