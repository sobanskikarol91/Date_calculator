#pragma once

#include <iostream>
using namespace std;

#define ILOSC_MIESIECY 12
#define DNI_PRZESTEPNE 366
#define DNI_NIEPRZESTEPNE 365
typedef unsigned short us;

class Data
{
	us dzien;
	us miesiac;
	us rok;
	short * dni_miesiaca;
public:
	Data() : Data(0, 0, 0) {}
	Data(us dzien) : Data(dzien, 0, 0) {}
	Data(us dzien, us miesiac, us rok) : dzien(dzien), miesiac(miesiac), rok(rok)
	{
		utworz_miesiace();
		cout << "Miesiac" << miesiac;
		try
		{
			sprawdzenie_daty();
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
		// usuwamy dynamicznie przydzielona pamiec
		delete[] dni_miesiaca;
	}

	Data operator+( int  dni)
	{
		int dni_do_dodania = oblicz_dni_od_poczatku_roku() + dni;
		int obliczony_rok = oblicz_lata(dni, rok);
		int obliczony_miesiac = oblicz_ile_miesiecy(dni, rok);
			
		return  Data(obliczony_rok, obliczony_miesiac, dni);
	}

	Data operator-(const Data & d)
	{
		return Data(dzien - d.dzien, miesiac - d.miesiac, rok - d.rok);
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
		cout << "miesiac" << miesiac << endl;
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
		dni_miesiaca = new short[ILOSC_MIESIECY] { 31, luty, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31};
	}

	// obliczamy ile lat jest z podanych dni
	us oblicz_lata(int & dni, us licz_od_roku)
	{
		short dni_w_roku;

		// jezeli dni jest wiecej niz w danym roku 
		while (dni > (dni_w_roku = ile_dni_ma_rok(rok)))
		{
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
			dni_roku += dni_miesiaca[i];

		return dni_roku;
	}

	short oblicz_ile_miesiecy(int & dni, int rok)
	{
		short dni_w_miesiacu, nr_miesiac = 1;

		// jezeli dni jest wiecej niz w danym roku 
		while (dni > (dni_w_miesiacu > dni_miesiaca[nr_miesiac - 1]))
		{
			dni -= dni_w_miesiacu;
			cout << dni << endl;
			nr_miesiac++;
		}
		// zwracamy ile jest pelnych miesiecy
		return nr_miesiac;
	}

	short ile_dni_ma_rok(short rok)
	{
		return czy_przestepny(rok) ? DNI_PRZESTEPNE : DNI_NIEPRZESTEPNE;
	}
};

