#include<iostream>
#include "Data.h"
using namespace std;

int main()
{
	Data d1(31,12,1945);
	int dni = 0;
	
	Data d3 = d1 + dni;

	cout << d1;
	cout << d3;
	getchar();
	return 0;
}