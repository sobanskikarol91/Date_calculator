#include<iostream>
#include "Data.h"
using namespace std;

int main()
{
	Data d1(12,06,2018), d2(20,19,20);
	int dni = 9000;
	
	Data d3 = d1 + dni;

	cout << d1;
	cout << d3;
	getchar();
	return 0;
}