#include <iostream>
#include "Algorithm.h"

using namespace std;


int main()
{
	//tree_23<int> t;
	//AVLtree<int> k;
	//int  i;
	//tree_23<int>::Node* m = t.getNext(i, 6);

	//k.insert(6);
	//k.insert(12);
	//AVLtree<int>::Node* l = k.getNext(6);

	//for (int i = 0; i < 10000; ++i)
	//	t.insert(i);
	////t.print();
	//for (int i = 0; i < 10000; ++i)
	//	t.remove(i);

	line* t = new line[10];
	t[0].set(1, 1, 4, 4);
	t[1].set(2, 2, 5, 5);
	t[2].set(3, 3, 6, 6);
	t[3].set(3, 3, 9, 9);
	t[4].set(5, 5, 8, 8);
	t[5].set(9, 9, 10, 10);
	t[6].set(-4, -4, -1, -1);
	t[7].set(-5, -4, 10, 0);
	t[8].set(-1, 0, 4, 0);
	t[9].set(0, 1, 0, 4);

	int s1, s2;
	int n = 10;
	bool m = func<AVLtree<CntPoint>>(t, n, s1, s2);

	return 0;
}