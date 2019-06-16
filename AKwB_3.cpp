// AKwB_3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>


using namespace std;

//pliki do odczytu
string fasta("6.fasta");
string qual("6.qual");


struct wierch {
	string kod;
	int nr_sekw; // to tez - pewnie bede zmienial 
	int pozycja; //wazne numeruje od 1
};

vector<wierch> gsekw;
vector<string> sekwencje;
vector<string> naglowki;
vector<vector<int> > quality;
vector<vector<int> > macierz;


//FUNKCJE
void Wczytanie2(string a, int dl_sekw, int numer)
{
	for (int i = 0; i < (a.length() - (dl_sekw - 1)); i++) //dlugosc sekw a - ostatnie litery ciagu ktrore nie utworza pelnego wierzcholka
	{
		gsekw.push_back(wierch()); // tworze obiekt strukt wierch

		gsekw[gsekw.size() - 1].kod = a.substr(i, dl_sekw); // no juz raczej wiadomo
		//cout << gsekw[gsekw.size() - 1].kod << endl;
		//_getch();
		gsekw[gsekw.size() - 1].nr_sekw = numer;
		gsekw[gsekw.size() - 1].pozycja = i + 1;
	}
}
void Wczytanie_fasta(int dl_sekw)
{
	fstream tenfasta;
	string linia, a;

	tenfasta.open(fasta.c_str(), ios::in);
	if (tenfasta.good())
	{
		int k = 0, numer = 0; //k to zabezpieczenie zeby wykonac pierwszego if za drugim | numer (sekwencji)

		while (!tenfasta.eof())
		{
			getline(tenfasta, linia); //biore cala linie z pliku

			if (linia[0] == '>') // i jesli ma dziubek 
			{
				naglowki.push_back(linia.substr(0, 15));
				if (k) // pomijam pierwsza iteracje bo nie ma sekwencji wczesniejszej
				{
					numer++; //inkrementuje numer sekw
					Wczytanie2(a, dl_sekw, numer); // ^^
					sekwencje.push_back(a);
				}
				a = ""; //czyszcze a ktore trzyma cala sekwencje do wczytania
				continue;
			}
			if (linia[0] != '>') // jesli go nie ma dodaje do a sekwencje
			{
				a.append(linia);
				k = 1; // odblokowuje wejscie do ifa
			}
		}
		numer++; // wczytanie ostatniej linii
		Wczytanie2(a, dl_sekw, numer);
		sekwencje.push_back(a);
		tenfasta.close();
	}
}
void Wczytanie_qual()
{
	fstream tenqual;

	int liczba;
	char znak;

	tenqual.open(qual.c_str(), ios::in);
	if (tenqual.good())
	{
		while (1)
		{
			tenqual >> liczba;//wczytuje liczbe

			if (!tenqual.fail())
			{
				quality[quality.size() - 1].push_back(liczba);
				continue;
			}
			else // ale jak okaze sie ze nie jest liczba 
			{
				while(1)
				{
					tenqual.clear(); // usuwam flage bledu 
					znak = tenqual.peek(); // sprawdzam kolejny znak
					if (isspace(znak)) // czy jest znakiem bialym 
					{
						tenqual.get(znak); // jak jest znakiem bialym
						if (znak == '\n') // wczytuje go i sprawdzam czy jest enterem
						{
							quality.push_back(vector<int>(0));
							break;
						}
					}
					tenqual >> znak; // jesli nie jest znakiem bialym wywalam wszystkie znaki
					if (tenqual.fail())
						break;
				}
			}
			if (tenqual.eof())
				break;
		}
	}
}  
int Dlugosc_sekwencji()
{
	int dl_sekw;
	while (1) //bezpieczne wczytywanie dlugosci sekwencji
	{
		cout << "Podaj dlugosc sekwencji w grafie (4-7): ";
		cin >> dl_sekw;

		if (dl_sekw == 4 || dl_sekw == 5 || dl_sekw == 6 || dl_sekw == 7)
		{
			cout << "Wybrany rozmiar sekwencji to: " << dl_sekw;
			return dl_sekw;
		}
		else
		{
			cout << endl << "PODANO ZLA LICZBE";
			continue;
		}

	}
}
int Ocena_wiarygodnosci()
{
	int ocena;
	while (1) //bezpieczne wczytywanie oceny jakosci
	{
		cout << endl << endl << "Podaj najnizsza wartosc oceny jakosci: ";
		cin >> ocena;

		if ((ocena > 0) && (ocena < 40))
		{
			cout << "Wybrana ocena: " << ocena << endl;
			return ocena;
		}
		else
		{
			cout << endl << "PODANO ZLA LICZBE!";
			continue;
		}

	}

}
void Wypisz_qual()
{
	for (int i = 0; i < quality.size(); i++)
	{
		_getch();
		cout << i << endl << ">sekwencja nr: " << i + 1 << endl;
		for (int j = 0; j < quality[i].size(); j++)
		{
			cout << quality[i][j] << " ";
		}
		cout << endl << endl;
	}
}
void Wypisz_sekw()
{
	for (int i = 0; i < gsekw.size(); i++)
	{
		cout << endl << "sekwention: " << gsekw[i].kod << " nr: " << gsekw[i].nr_sekw << " position: " << gsekw[i].pozycja << endl;
		_getch();
	}
}
void Stworz_macierz()
{
	vector<int> rows(gsekw.size(), 0);
	for (int i = 0; i < gsekw.size(); i++)
	{
		macierz.push_back(rows);
	}
}
void Drukuj_macierz(/*int wymiar, int dwa*/)
{
	for (int i = 0; i < macierz.size(); i++)
	{
		cout << i << ".  ";
		//_getch();
		for (int j = 0; j < macierz[i].size(); j++)
		{
			cout << macierz[i][j] << " ";
		}
		cout << endl;
	}
	/*cout << endl << endl;
	cout << wymiar << ".  ";
	for (int i = 0; i < macierz[wymiar].size(); i++)
	{
		cout << macierz[wymiar][i] << " ";
		if (macierz[wymiar][i]) { cout << i; }
	}
	
	cout << endl << dwa << ".  ";
	for (int i = 0; i < macierz[dwa].size(); i++)
	{
		cout << macierz[dwa][i] << " ";
	}*/
}
void Wypelnij_macierz(int dl_sekw, int ocena)
{
	for (int i = 0; i < gsekw.size(); i++) //przechodze pierwszy przez sekwencje
	{
		for (int j = i; j < gsekw.size(); j++) //przechodze drugi przez sekwencje (the same) - j = i aby nie przechodzic porownywac tych samych sekwencji
		{
			if (gsekw[i].nr_sekw != gsekw[j].nr_sekw) // juz sie zgadza nic sie nie powtarza
			{
				int poprawne = 0;
				int delicje = 0;
				for (int k = 0; k < dl_sekw; k++) //przechodze przez kazdy oligonukleotyd po pojedynczych literach 
				{
					//cout << endl << gsekw[i].kod[k] << " " << quality[gsekw[i].nr_sekw - 1][gsekw[i].pozycja - 1 + k] << "  " << gsekw[j].kod[k] << " " << quality[gsekw[j].nr_sekw - 1][gsekw[j].pozycja - 1 + k];
					if (gsekw[i].kod[k] == gsekw[j].kod[k])
					{
						poprawne += 1;
						//cout << "<--";
					}
					else if((quality[gsekw[i].nr_sekw - 1][gsekw[i].pozycja - 1 + k] <= ocena) || (quality[gsekw[j].nr_sekw - 1][gsekw[j].pozycja - 1 + k] <= ocena))
					{
						poprawne += 1;
						delicje += 1;
						if (delicje > 1)
						{
							poprawne = 0;
							break;
						}
						//cout << "<--";
					}
					//_getch();
				}
				//_getch();
				if (poprawne == dl_sekw)
				{
					//cout << " " << poprawne << endl;
					//cout << endl;            // Pamietaj ze w macierzy sa wierzchołki a nie sekwencja - inne numerowanie, 
					macierz[i][j] = 1;		 // brak spojnosci pozycji, wiersz macierzy ma dlugosc = liczbie wierzcholkow
					macierz[j][i] = 1; //EDIT: TAK SERIO TO NIE TO SAMO?
					//Drukuj_macierz(i, j);
					//_getch();
				}
				//cout << endl;

			}
			//_getch();
		}
		//_getch();
	}
}
int Wyszukaj_dobre_wierz()
{
	int licznik = 0, max = 0; //po 3 dobrym wierzcholku wroc do main
	int wierzcholek = 0, numerosek = 0;
	for (int i = 0; i < macierz.size(); i++)
	{
		//cout << i << " OBROT " <<endl;
		int polaczenia = 0;
		for (int j = 0; j < macierz[i].size(); j++)
		{
			if (macierz[i][j] == 0) //brak polaczenia
				continue;
			else if(gsekw[j].nr_sekw != numerosek) //czy obiekt nie pochodzi z tej samej sekwencji
			{
				numerosek = gsekw[j].nr_sekw;
				polaczenia += 1; //zlicz polaczenia "NIBY KLIKI"
				//cout << gsekw[j].nr_sekw << " <> " << polaczenia << endl;
			}
		}
		if (polaczenia < 3) //jesli mniej niz trzy to szukej do konca macierzy... Jakas optymalizacja? :/
			continue;
		else
		{
			if (polaczenia > max) //sprawdzaj czy jest wieksza niby klika
			{
				wierzcholek = i; //nie zgub wierzcholka
				max = polaczenia; //Ustal "rekord" polaczen 
			}
			licznik += 1; //szukaj max 3 razy najwiekszej niby kliki w ultraniby optymalizacji
			if (licznik == 3) 
			{
				return wierzcholek;
			}
		}
	}
}

//______________________________________________________________________________________________________________________________
int main()
{
	//Dlugosc ramki tworzenia obiektów
	int dl_sekw = 5; //Dlugosc_sekwencji(); 
	int ocena = 30; // Ocena_wiarygodnosci();

	cout << endl << endl << "Wczytuje dane i tworze graf...";
	Wczytanie_fasta(dl_sekw);
	//Wypisz_sekw();

	Wczytanie_qual();
	//Wypisz_qual();
	cout << "\t" << "Gotowe!" << endl << "Tworze macierz...";

	Stworz_macierz();
	//Drukuj_macierz();
	cout << "\t\t" << "Gotowe!" << endl << "Wypelniam macierz...";
	
	Wypelnij_macierz(dl_sekw, ocena); //MAMY MACIERZ
	cout << "\t\t" << "Gotowe!" << endl << "Wyszukiwanie wierzcholkow...";
	//Drukuj_macierz();
	int wierzcholek = Wyszukaj_dobre_wierz();
	cout << "\t" << "Gotowe!" << endl;

	cout << endl << endl << "Motyw: " << gsekw[wierzcholek].kod << " znaleziony w sekwencji " << naglowki[gsekw[wierzcholek].nr_sekw - 1]<< ": " << endl;

	int numerosek = 0;
	for (int j = 0; j < macierz[wierzcholek].size(); j++)
	{
		if (macierz[wierzcholek][j] && (numerosek != gsekw[j].nr_sekw))
		{
			cout << endl << naglowki[gsekw[j].nr_sekw - 1] << " na pozycji - S: " << gsekw[j].pozycja << " E: " << gsekw[j].pozycja + dl_sekw - 1;
			cout << " sekw: " << setw(8) << gsekw[j].kod;
			numerosek = gsekw[j].nr_sekw;
		}
		
	}

	cout << endl << endl;
	return 0;
}
