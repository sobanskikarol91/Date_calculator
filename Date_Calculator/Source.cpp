#include<iostream>
#include "Data.h"
using namespace std;

int main()
{
	//Data d1(12,06,2018), d2(20,04,20);
	int dni = 9000;
	Data d1(31, 12, 2018), d2(31, 12, 20);
	Data d3 = d1  - 900;

	cout << d1;
	cout << d2;

	cout << d3;
	getchar();
	return 0;
}