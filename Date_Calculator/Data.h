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
		int obliczony_rok = oblicz_lata_po_dodaniu_dni(suma_dni_do_dodania, rok);
		cout << "dni od poczatku:" << suma_dni_do_dodania << endl;
		int obliczony_miesiac = oblicz_ile_miesiecy(suma_dni_do_dodania, obliczony_rok);
		cout << "dni od poczatku:" << suma_dni_do_dodania << endl;

		return Data(suma_dni_do_dodania, obliczony_miesiac, obliczony_rok);
	}

	Data operator+(Data data)
	{
		int dni_do_dodania = oblicz_dni_od_poczatku_roku() + data.oblicz_dni_od_poczatku_roku();
		cout << "Dni od poczatku: " << dni_do_dodania << endl;

		int obliczony_rok = oblicz_lata_po_dodaniu_dni(dni_do_dodania, rok + data.rok);
		cout << "Dni na miesiace: " << dni_do_dodania << endl;
		int obliczony_miesiac = oblicz_ile_miesiecy(dni_do_dodania, obliczony_rok);

		return  Data(dni_do_dodania, obliczony_miesiac, obliczony_rok);
	}

	Data operator-(int dni_ktore_odejmujemy)
	{
		int roznica_dni = oblicz_dni_od_poczatku_roku() - dni_ktore_odejmujemy;
		int obliczony_rok=rok, obliczony_miesiac = 0;
		cout << "Roznica dni: " << roznica_dni << endl;

		if (roznica_dni < 0)
		{
			roznica_dni *= (-1);
			obliczony_rok = oblicz_lata_po_odjeciu_dni(roznica_dni, rok);
			cout << "Roznica lat:" << obliczony_rok << endl;
		}
		if(roznica_dni > 0)
		{
			 obliczony_miesiac = oblicz_ile_miesiecy(roznica_dni, obliczony_rok);
		}

		return Data(roznica_dni, obliczony_miesiac, obliczony_rok);
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
		dni_miesiaca = new int[ILOSC_MIESIECY] { 31, luty, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	}


	int oblicz_lata_po_dodaniu_dni(int & dni_do_dodania, int licz_od_roku)
	{
		int dni_w_roku;

		// jezeli dni jest wiecej niz w danym roku 
		while (dni_do_dodania > (dni_w_roku = ile_dni_ma_rok(licz_od_roku)))
		{
			cout << "rok: " << licz_od_roku << "  " << ile_dni_ma_rok(licz_od_roku) << endl;
			dni_do_dodania -= dni_w_roku;
			cout << dni_do_dodania << endl;
			licz_od_roku++;
		}
		return licz_od_roku;
	}

	int oblicz_lata_po_odjeciu_dni(int & pozostale_dni, int licz_od_roku)
	{
		int dni_w_roku;

		cout << "ile dni przed odejmowaniem " << pozostale_dni << endl;

		while (pozostale_dni > 0)
		{
			dni_w_roku = ile_dni_ma_rok(licz_od_roku);
			cout << "Dni w roku: " << dni_w_roku << "  Odejmij" << pozostale_dni << endl;

			dni_w_roku -= pozostale_dni;
			pozostale_dni -= ile_dni_ma_rok(licz_od_roku);
			licz_od_roku--;
		}

		pozostale_dni = dni_w_roku;
		cout << "dni po udejmownaiu: " << dni_w_roku << endl;
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

		cout << "dni od poczatku:" << dni_roku << endl;
		return dni_roku;
	}

	short oblicz_ile_miesiecy(int & pozostale_dni, int obliczony_rok)
	{
		short dni_w_miesiacu = 0, nr_miesiac = 1;

		cout << "Oblicz miesiace: " << pozostale_dni << endl;
		// jezeli dni jest wiecej niz w danym roku 

		while (pozostale_dni > (dni_w_miesiacu = oblicz_ile_dni_w_miesiacu(obliczony_rok, nr_miesiac - 1)) )
		{
			cout << "Od Dni: " << pozostale_dni << " Odejmnij: " << dni_w_miesiacu << endl;
			pozostale_dni -= dni_w_miesiacu;
			cout << pozostale_dni << endl;
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

