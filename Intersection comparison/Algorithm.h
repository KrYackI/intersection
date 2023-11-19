#pragma once
#include "2,3-tree.h"
#include "AVL_tree.h"
#include "line.h"
#include <Algorithm>

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
		cout << pointArr[i].first.x << ' ' << pointArr[i].first.y << ' ' << pointArr[i].second << '\n';
	}

	for (int i = 0; i < 2 * n; ++i)
	{
		point p = pointArr[i].first;
		int l = pointArr[i].second;
		CntPoint cpt(p, arr + l);
		if (p == arr[l].getLeft())
		{
			cont.insert(cpt);
			if (cont.getPrev(cpt))
			{
				line* l1 = cont.getPrevItem(cpt).ln;
				if (l1->intersect(arr[l]))
				{
					s1 = l1 - arr;
					s2 = l;
					return true;
				}
			}
			if (cont.getNext(cpt))
			{
				line* l2 = cont.getNextItem(cpt).ln;
				if (l2->intersect(arr[l]))
				{
					s1 = l;
					s2 = l2 - arr;
					return true;
				}
			}
		}
		else
		{
			if (cont.getNext(cpt) && cont.getPrev(cpt))
			{
				line* l1 = cont.getPrevItem(cpt).ln;
				line* l2 = cont.getNextItem(cpt).ln;
				if (l1->intersect(*l2))
				{
					s1 = l1 - arr;
					s2 = l2 - arr;
					return true;
				}
			}
			cont.remove(cpt);
		}
	}
	return false;
}