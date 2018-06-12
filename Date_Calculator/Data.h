#pragma once

#include <iostream>
using namespace std;

#define ILOSC_MIESIECY 12
#define DNI_PRZESTEPNE 366
#define DNI_NIEPRZESTEPNE 365
typedef unsigned int ui;

class Data
{
	ui dzien;
	ui miesiac;
	ui rok;
	short * dni_miesiaca;
public:
	Data() : Data(0, 0, 0) {}
	Data(ui dzien) : Data(dzien, 0, 0) {}
	Data(ui dzien, ui miesiac, ui rok) : dzien(dzien), miesiac(miesiac), rok(rok)
	{
		utworz_miesiace();
		try
		{
			//sprawdzenie_daty();
		}
		catch (ui blad)
		{
			if (blad == 0) cerr << "Niepoprawny miesiac i dzien" << endl;
			else if (blad == 1) cerr << "Niepoprawny miesiac" << endl;
			else if (blad == 2) cerr << "Niepoprawny dzien" << endl;

			*this = Data(); // inicjalizujemy wszystko zerami.
		}
	}

	~Data()
	{
		// uiuwamy dynamicznie przydzielona pamiec
		delete[] dni_miesiaca;
	}

	Data operator+(ui dodaj_dni)
	{
		ui suma_dni_do_dodania = oblicz_dni_od_poczatku_roku() + dodaj_dni;
		ui obliczony_rok = oblicz_lata(suma_dni_do_dodania, rok);
		cout << "dni od poczatku:" << suma_dni_do_dodania << endl;
		ui obliczony_miesiac = oblicz_ile_miesiecy(suma_dni_do_dodania, obliczony_rok);
		cout << "dni od poczatku:" << suma_dni_do_dodania << endl;

		return Data(suma_dni_do_dodania, obliczony_miesiac, obliczony_rok);
	}

	Data operator+(Data data)
	{
		ui dni_do_dodania = oblicz_dni_od_poczatku_roku() + data.oblicz_dni_od_poczatku_roku();
		cout << "Dni od poczatku: " << dni_do_dodania << endl;
		
		ui obliczony_rok =  oblicz_lata(dni_do_dodania, rok + data.rok);
		ui obliczony_miesiac = oblicz_ile_miesiecy(dni_do_dodania, obliczony_rok);


		return  Data(dni_do_dodania, obliczony_miesiac, obliczony_rok);
	}


	friend ostream & operator<<(ostream & ekran, const  Data & d)
	{
		return ekran << d.dzien << "-" << d.miesiac << "-" << d.rok << endl;
	}

	bool czy_przestepny(ui rok)
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
		dni_miesiaca = new short[ILOSC_MIESIECY] { 31, luty, 31, 30, 31, 31, 30, 31, 30, 31, 30, 31};
	}

	// obliczamy ile lat jest z podanych dni
	ui oblicz_lata(ui & dni, ui licz_od_roku)
	{
		ui dni_w_roku;

		// jezeli dni jest wiecej niz w danym roku 
		while (dni > (dni_w_roku = ile_dni_ma_rok(licz_od_roku)))
		{
			cout << "rok: " << licz_od_roku << "  " << ile_dni_ma_rok(licz_od_roku) << endl;
			dni -= dni_w_roku;
			//cout << dni << endl;
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

	short oblicz_ile_miesiecy(ui & dni, ui obliczony_rok)
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

	ui ile_dni_ma_rok(ui rok)
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

