#pragma once

#include <iostream>
using namespace std;

#define ILOSC_MIESIECY 12
#define DNI_PRZESTEPNE 366
#define DNI_NIEPRZESTEPNE 365

class Data
{
	int dzien;
	int miesiac;
	int rok;
	int * dni_miesiaca;
public:
	Data() : Data(0, 0, 0) {}
	Data(int dzien) : Data(dzien, 0, 0) {}
	Data(int dzien, int miesiac, int rok) : dzien(dzien), miesiac(miesiac), rok(rok)
	{
		utworz_miesiace();
		try
		{
			//sprawdzenie_daty();
		}
		catch (int blad)
		{
			if (blad == 0) cerr << "Niepoprawny miesiac i dzien" << endl;
			else if (blad == 1) cerr << "Niepoprawny miesiac" << endl;
			else if (blad == 2) cerr << "Niepoprawny dzien" << endl;

			*this = Data(); // inicjalizujemy wszystko zerami.
		}
	}

	~Data()
	{
		// intuwamy dynamicznie przydzielona pamiec
		delete[] dni_miesiaca;
	}

	Data operator+(int dodaj_dni)
	{
		int suma_dni_do_dodania = oblicz_dni_od_poczatku_roku() + dodaj_dni;
		int obliczony_rok = oblicz_lata(suma_dni_do_dodania, rok);
		cout << "dni od poczatku:" << suma_dni_do_dodania << endl;
		int obliczony_miesiac = oblicz_ile_miesiecy(suma_dni_do_dodania, obliczony_rok);
		cout << "dni od poczatku:" << suma_dni_do_dodania << endl;

		return Data(suma_dni_do_dodania, obliczony_miesiac, obliczony_rok);
	}

	Data operator+(Data data)
	{
		int dni_do_dodania = oblicz_dni_od_poczatku_roku() + data.oblicz_dni_od_poczatku_roku();
		cout << "Dni od poczatku: " << dni_do_dodania << endl;
		
		int obliczony_rok =  oblicz_lata(dni_do_dodania, rok + data.rok);
		cout << "Dni na miesiace: " << dni_do_dodania << endl;
		int obliczony_miesiac = oblicz_ile_miesiecy(dni_do_dodania, obliczony_rok);

		return  Data(dni_do_dodania, obliczony_miesiac, obliczony_rok);
	}

	Data operator-(int dni_ktore_odejmujemy)
	{
		int roznica_dni = oblicz_dni_od_poczatku_roku() -  dni_ktore_odejmujemy;
		cout << "Dni od poczatku " << dni_ktore_odejmujemy;
		int obliczony_rok=0;
		cout << "Roznica dni: " << roznica_dni << endl;
		if (roznica_dni)
		{

		}
		else
		{
			roznica_dni *= (-1);
			obliczony_rok = rok - oblicz_lata(roznica_dni, rok);
			cout << "Roznica lat:" << obliczony_rok << endl;

		}

		//int obliczony_miesiac = oblicz_ile_miesiecy(suma_dni_do_dodania, obliczony_rok);
		//cout << "dni od poczatku:" << suma_dni_do_dodania << endl;

		return Data(0, 0, obliczony_rok);
	}


	friend ostream & operator<<(ostream & ekran, const  Data & d)
	{
		return ekran << d.dzien << "-" << d.miesiac << "-" << d.rok << endl;
	}

	bool czy_przestepny(int rok)
	{
		return ((rok % 4 == 0) && (rok % 100 != 0)) || (rok % 400 == 0);
	}

	void sprawdzenie_daty()
	{
		//cout << "miesiac" << miesiac << endl;
		bool miesiace_blad, dni_blad;
		miesiace_blad = miesiac > ILOSC_MIESIECY;
		dni_blad = dzien > dni_miesiaca[miesiac - 1];


		if (miesiace_blad && dni_blad) throw 0;
		else if (miesiace_blad) throw 1;
		else if (dni_blad) throw 2;
	}

public:
	void utworz_miesiace()
	{
		short luty = czy_przestepny(rok) ? 29 : 28;
		// tworzymy dynamicznie aby to od razu zainicjalizowac w 1 linijce
		dni_miesiaca = new int[ILOSC_MIESIECY] { 31, luty, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31};
	}

	// obliczamy ile lat jest z podanych dni
	int oblicz_lata(int & dni, int licz_od_roku)
	{
		int dni_w_roku;

		// jezeli dni jest wiecej niz w danym roku 
		while (dni > (dni_w_roku = ile_dni_ma_rok(licz_od_roku)))
		{
			cout << "rok: " << licz_od_roku << "  " << ile_dni_ma_rok(licz_od_roku) << endl;
			dni -= dni_w_roku;
			cout << dni << endl;
			licz_od_roku++;
		}
		return licz_od_roku;
	}

public:
	// obliczamy dni ktore uplynely od poczatku roku
	short oblicz_dni_od_poczatku_roku()
	{
		// dodajemy wszystkie dni
		short dni_roku = this->dzien;

		// dodajemy pelne miesiace do dni
		for (size_t i = 0; i < miesiac - 1; i++)
			dni_roku += oblicz_ile_dni_w_miesiacu(rok,i);

		cout << "dni od poczatku:" << dni_roku << endl;
		return dni_roku;
	}

	short oblicz_ile_miesiecy(int & dni, int obliczony_rok)
	{
		short dni_w_miesiacu=0, nr_miesiac = 1;

		cout << "Obliczony rok: " << obliczony_rok << endl;
		// jezeli dni jest wiecej niz w danym roku 
		while (dni > (dni_w_miesiacu = oblicz_ile_dni_w_miesiacu(obliczony_rok, nr_miesiac -1)))
		{
			cout << "Od Dni: " << dni << " Odejmnij: " << dni_w_miesiacu << endl;
			dni -= dni_w_miesiacu;
			cout << dni << endl;
			nr_miesiac++;
		}
		// zwracamy ile jest pelnych miesiecy
		return nr_miesiac;
	}

	int ile_dni_ma_rok(int rok)
	{
		return czy_przestepny(rok) ? DNI_PRZESTEPNE : DNI_NIEPRZESTEPNE;
	}

	short oblicz_ile_dni_w_miesiacu(short podany_rok, short miesiac)
	{
		if (miesiac == 1 && czy_przestepny(podany_rok)) return 29;

		else if (miesiac == 1 && !czy_przestepny(podany_rok)) return 28;
		else return dni_miesiaca[miesiac];
	}
};

