#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "Algorithm.h"
#include "Generator.h"

//#define EXPERIMENT

#ifdef EXPERIMENT

#define MAX_N 100000
#define SPACE 1000
#define MAX_R 0.01
#define SPACE_R 0.0001

using namespace std;


int main()
{
	srand(time(0));
	ofstream out;
	out.open("speedtestW23height.txt");
	cout << "first round : ";
	for (int n = 1; n < MAX_N + 1; n += SPACE)
	{
		int s1 = 0, s2 = 0, s3 = 0, s4 = 0, h1 = 0, h2 = 0;
		line* lines = generate1(n);
		clock_t start1 = clock();
		funcAVL(lines, n, s1, s2, h1);
		clock_t end1 = clock();
		clock_t start2 = clock();
		func23(lines, n, s3, s4, h2);
		clock_t end2 = clock();
		double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
		double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
		out << seconds1 << ' ' << h1 << ' ' << seconds2 << ' ' << h2 << '\n';
		if (s1 != s3 || s2 != s4)
			cout << n << endl;
		delete[] lines;
	}
	cout << "done" << endl;
	out << '\n';
	cout << "second round : ";
	for (int k = 1; k < MAX_N + 1; k += SPACE)
	{
		int s1 = 0, s2 = 0, s3 = 0, s4 = 0, h1 = 0, h2 = 0;
		line* lines = generate1(MAX_N + 3, k);
		clock_t start1 = clock();
		funcAVL(lines, MAX_N + 3, s1, s2, h1);
		clock_t end1 = clock();
		clock_t start2 = clock();
		func23(lines, MAX_N + 3, s3, s4, h2);
		clock_t end2 = clock();
		double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
		double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
		out << seconds1 << ' ' << h1 << ' ' << seconds2 << ' ' << h2 << '\n';
		if (s1 != s3 || s2 != s4)
			cout << k << endl;
		delete[] lines;
	}
	cout << "done" << endl;
	out << '\n';
	cout << "third round : ";
	for (int n = 1; n < MAX_N + 1; n += SPACE)
	{
		int s1 = 0, s2 = 0, s3 = 0, s4 = 0, h1 = 0, h2 = 0;
		line* lines = generate2(n, 0.001);
		clock_t start1 = clock();
		funcAVL(lines, n, s1, s2, h1);
		clock_t end1 = clock();
		clock_t start2 = clock();
		func23(lines, n, s3, s4, h2);
		clock_t end2 = clock();
		double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
		double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
		out << seconds1 << ' ' << h1 << ' ' << seconds2 << ' ' << h2 << '\n';
		if (s1 != s3 || s2 != s4)
			cout << n << endl;
		delete[] lines;
	}
	cout << "done" << endl;
	out << '\n';
	cout << "fourth round : ";
	for (double r = SPACE_R; r < MAX_R; r += SPACE_R)
	{
		int s1 = 0, s2 = 0, s3 = 0, s4 = 0, h1 = 0, h2 = 0;
		line* lines = generate2(MAX_N, r);
		clock_t start1 = clock();
		funcAVL(lines, MAX_N, s1, s2, h1);
		clock_t end1 = clock();
		clock_t start2 = clock();
		func23(lines, MAX_N, s3, s4, h2);
		clock_t end2 = clock();
		double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
		double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
		out << seconds1 << ' ' << h1 << ' ' << seconds2 << ' ' << h2 << '\n';
		if (s1 != s3 || s2 != s4)
			cout << r << endl;
		delete[] lines;
	}
	cout << "done" << endl;
	out.close();
	return 0;
}
#else

int main()
{
	string filename;
	cin >> filename;
	ifstream in(filename);
	if (in.is_open())
	{
		int n, h = 0;
		line* arr = enter(in, n);
		int s1 = 0, s2 = 0;
		bool f = funcAVL(arr, n, s1, s2, h);
		ofstream out;
		out.open("AVL.txt");
		out << f << ' ' << s1 << ' ' << s2;
		out.close();
		f = func23(arr, n, s1, s2, h);
		out.open("23.txt");
		out << f << ' ' << s1 << ' ' << s2;
		out.close();
	}
	return 0;
}

#endif