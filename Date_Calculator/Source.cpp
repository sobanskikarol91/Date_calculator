#include<iostream>
#include "Data.h"
using namespace std;

#include <string>


void linux(int argc, char* argv[])
{
	if (*argv[2] == '+')
		cout << Data(argv[1]) << " + " << Data(argv[3]) << " = " << Data(argv[1]) + Data(argv[3]) << endl;
	else if (*argv[2] == '-')
		cout << Data(argv[1]) << " - " << Data(argv[3]) << " = " << Data(argv[1]) - Data(argv[3]) << endl;

	getchar();
}


int main(int argc, char* argv[])
{
	char sciezka[] = "./plik";
	char data1[] = "10-03-0105";
	char znak[1]{ '+' };
	char data2[] = "10-07-1205";

	const int rozmiar = 4;
	char * wskaznik[rozmiar];
	wskaznik[0] = sciezka;
	wskaznik[1] = data1;
	wskaznik[2] = znak;
	wskaznik[3] = data2;
	linux(rozmiar, wskaznik);
	return 0;
}
