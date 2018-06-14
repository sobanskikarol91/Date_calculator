#pragma once

#include <iostream>
#include <string>
using namespace std;

#define ILOSC_MIESIECY 12
#define DNI_PRZESTEPNE 366
#define DNI_NIEPRZESTEPNE 365

class Data
{
	int dzien;
	int miesiac;
	int rok;
	int dni_miesiaca[ILOSC_MIESIECY] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

public:
	Data() : Data(0, 0, 0) {}
	Data(int dzien) : Data(dzien, 0, 0) {}

	Data(string data) : Data(stoi(data.substr(0, 2)), stoi(data.substr(3, 2)), stoi(data.substr(6, 4))) {}

	Data(int dzien, int miesiac, int rok) : dzien(dzien), miesiac(miesiac), rok(rok) {}

	Data operator+(int dodaj_dni)
	{
		int suma_dni_do_dodania = oblicz_dni_od_poczatku_roku() + dodaj_dni;
		int obliczony_rok = oblicz_lata_po_dodaniu_dni(suma_dni_do_dodania, rok);
		int obliczony_miesiac = oblicz_ile_miesiecy(suma_dni_do_dodania, obliczony_rok);
		return Data(suma_dni_do_dodania, obliczony_miesiac, obliczony_rok);
	}

	Data operator+(Data data)
	{
		int dni_do_dodania = oblicz_dni_od_poczatku_roku() + data.oblicz_dni_od_poczatku_roku();
		int obliczony_rok = oblicz_lata_po_dodaniu_dni(dni_do_dodania, rok + data.rok);
		int obliczony_miesiac = oblicz_ile_miesiecy(dni_do_dodania, obliczony_rok);

		return  Data(dni_do_dodania, obliczony_miesiac, obliczony_rok);
	}

	Data operator-(int dni_ktore_odejmujemy)
	{
		int roznica_dni = oblicz_dni_od_poczatku_roku() - dni_ktore_odejmujemy;
		int obliczony_rok = rok, obliczony_miesiac = 0;

		if (roznica_dni < 0)
		{
			roznica_dni *= (-1);
			obliczony_rok = oblicz_lata_po_odjeciu_dni(roznica_dni, rok);
		}
		if (roznica_dni > 0)
			obliczony_miesiac = oblicz_ile_miesiecy(roznica_dni, obliczony_rok);

		return Data(roznica_dni, obliczony_miesiac, obliczony_rok);
	}

	Data operator-(Data data)
	{
		int dni = zamien_date_na_dni(data);
		return *this - dni;
	}

	int zamien_date_na_dni(Data data)
	{
		int dni = 0;

		// lata na dni
		for (size_t i = 1; i < data.rok; i++)
			dni += ile_dni_ma_rok(i);

		// miesiace na dni
		for (size_t i = 0; i < data.miesiac; i++)
			dni += oblicz_ile_dni_w_miesiacu(data.rok, i);

		// dni
		dni += data.dzien;
		return dni;
	}

	friend ostream & operator<<(ostream & ekran, const  Data & d)
	{
		return ekran << d.dzien << "-" << d.miesiac << "-" << d.rok;
	}

	bool czy_przestepny(int rok)
	{
		return ((rok % 4 == 0) && (rok % 100 != 0)) || (rok % 400 == 0);
	}

public:

	int oblicz_lata_po_dodaniu_dni(int & dni_do_dodania, int licz_od_roku)
	{
		int dni_w_roku;

		// jezeli dni jest wiecej niz w danym roku 
		while (dni_do_dodania > (dni_w_roku = ile_dni_ma_rok(licz_od_roku)))
		{
			dni_do_dodania -= dni_w_roku;
			licz_od_roku++;
		}
		return licz_od_roku;
	}

	int oblicz_lata_po_odjeciu_dni(int & pozostale_dni, int licz_od_roku)
	{
		int dni_w_roku;


		while (pozostale_dni > 0)
		{
			dni_w_roku = ile_dni_ma_rok(licz_od_roku);
			dni_w_roku -= pozostale_dni;
			pozostale_dni -= ile_dni_ma_rok(licz_od_roku);
			licz_od_roku--;
		}

		pozostale_dni = dni_w_roku;
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
			dni_roku += oblicz_ile_dni_w_miesiacu(rok, i);

		return dni_roku;
	}

	short oblicz_ile_miesiecy(int & pozostale_dni, int obliczony_rok)
	{
		short dni_w_miesiacu = 0, nr_miesiac = 1;

		while (pozostale_dni > (dni_w_miesiacu = oblicz_ile_dni_w_miesiacu(obliczony_rok, nr_miesiac - 1)))
		{
			pozostale_dni -= dni_w_miesiacu;
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