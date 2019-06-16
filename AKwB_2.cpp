#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <string>
#include <stdlib.h>

using namespace std;

vector<int> rows(0, 0);
vector<vector<int> > lnast(0, rows); //sprzezony
 
vector<int> rzed(0, 0);
vector<vector<int> > graf(0, rzed); //oryginalny

void Wczytaj_graf()
{
	fstream plik;
	plik.open("graf_sprzez.txt", ios::in);

	if (plik.good())
	{
		while (!plik.eof())
		{
			if (plik.good())
			{
				string znak;
				getline(plik, znak);

				//cout << znak;

				if (znak == ";") //Tworzy nowy "wierzcholek" do vectora
				{
					lnast.push_back(vector<int>(0, 0));
					continue;
				}
				else //Dodaje do listy nastepnikow, nastepniki (pierwszy to wierzcholek)
				{
					int i = atoi(znak.c_str());
					lnast[lnast.size() - 1].push_back(i);
					continue;
				}
			}
		}
	}
	else
		cout << "blad wczytywania pliku :)" << endl;
	plik.close();
}
void Wypisz_lnast()
{
	for (int i = 0; i < lnast.size(); i++)
	{
		cout << lnast[i][0] << ": ";
		for (int j = 1; j < lnast[i].size(); j++)
		{
			cout << lnast[i][j] << " ";
		}
		cout << endl;
	}
}
void Wypisz_graf()
{
	for (int i = 0; i < graf.size(); i++)
	{
		cout << graf[i][0] << ": ";
		for (int j = 1; j < graf[i].size(); j++)
		{
			cout << graf[i][j] << " ";
		}
		cout << endl;
	}
}
int Poprawnosc_grafu()
{
	//Sprawdzam, czy kazdy luk ma zakonczenie w istniejacym wierzcholku
	for (int i = 0; i < lnast.size(); i++)
	{
		for (int j = 1; j < lnast[i].size(); j++)
		{
			for (int k = 0; k < lnast.size(); k++)
			{
				if (lnast[i][j] == lnast[k][0])
					break;
				if (k == (lnast.size()-1))
				{
					cout << "Nie istnieje wierzcholek: " << lnast[i][j] << endl;
					return 1;
				}
			}
		}
	}
	return 0;
}
int Sprawdz_sprzezenie()
{
	for (int i = 0; i < lnast.size(); i++) //wier1
	{
		for (int j = 1; j < lnast[i].size(); j++) //kol1 --1
		{
			for (int k = 1; k < lnast[i].size(); k++)
			{
				if (k == j)
					continue;
				if (lnast[i][j] == lnast[i][k])
				{
					cout << endl << "graf jest multigrafem!" << endl;
					return 0;
				}
			}
		}
	}
	for (int i = 0; i < lnast.size(); i++)//Kol
	{
		for (int j = 1; j < lnast[i].size(); j++)//Wier
		{
			for (int k = i+1; k < lnast.size(); k++)//Kol2
			{
				for (int l = 1; l < lnast[k].size(); l++)//Wier2
				{
					if (lnast[i][j] == lnast[k][l]) //Sprawdza czy jest powtorzony
					{
						if (lnast[i].size() == lnast[k].size()) //Sprawdza czy powtorzony jest tej samej dlugosci
						{
							for (int m = 1; m < lnast[i].size(); m++)
							{
								for (int n = 1; n < lnast[k].size(); n++)
								{
									if (lnast[i][m] == lnast[k][n]) //Sprawdza czy wszystkie sa takie same
										break;
									if (n == (lnast[k].size()-1))
										return 0; //sprawdzana liczba nie wystepuje w nastepnikach "tego drugiego"
								}
							}
						}
						else
						{
							return 0; //powtorzone nastepniki ale nie ta sama ilosc
						}
					}
				}
			}
		}
	}
	return 1; //jest sprzezony
}
int Sprawdz_liniowy()
{
	for (int i = 0; i < lnast.size(); i++) //wier1
	{
		for (int j = 1; j < lnast[i].size(); j++) //kol1 --1
		{
			for (int k = 0; k < lnast.size(); k++)  //wyszukiwanie 1 wierzcholka -----przechodze przez dostepne wierzcholki --1
			{
				if (lnast[i][j] == lnast[k][0]) //znaleziony wierzcholek -------porownuje element nastepnikow pierwszego wierzcholka z dostepnymi w celu znalezienia go
				{
					for (int l = 1; l < lnast[k].size(); l++) //przejscie przez wierzcholek nr 1 --1
					{
						for (int n = 1; n < lnast[i].size(); n++)
						{
							if (lnast[i][j] == lnast[i][n])
								continue;
							else
							{
								for (int p = 0; p < lnast.size(); p++)
								{
									if (lnast[i][n] == lnast[p][0])
									{
										for (int r = 1; r < lnast[p].size(); r++)
										{
											if (lnast[p][r] == lnast[k][l])
											{
												//cout << lnast[i][0] << "ij" << lnast[i][j] << " " <<lnast[k][0] << "kl" << lnast[k][l] << " " << lnast[p][0] << "pr" << lnast[p][r] << endl;
												return 0;
											}
										}

									}
								}
							}
								
						}

					}
				}
			}

		}
	}
	return 1;
}
void Przygotuj_vector()
{
	int k = 1;
	for (int i = 0; i < lnast.size(); i++)
	{
		graf.push_back(vector<int>(0, 0));

		for (int j = 0; j < 2; j++)
		{
			graf[i].push_back(k);
			k++;
		}
	}
	//Wypisz_graf();
}
void Uporzadkuj()
{
	int n = 1, k = 0;
	while (n)
	{
		k = 0;
		for (int i = 0; i < graf.size(); i++)
		{
			if (k) { break; }
			for (int j = 0; j < graf.size(); j++)
			{
				if (i == j) { continue; }
				if (graf[i][0] == graf[j][0])
				{
					graf[i].push_back(graf[j][1]);
					graf.erase(graf.begin() + j);

					k = 1;
					break;
				}
			}
			if (k) { break; }
			if (i == (graf.size() - 1)) { n = 0; }
		}
	}
}
void Przeksztalcenie()
{
	Przygotuj_vector();
	//cout << "gotowy" << endl;

	for (int i = 0; i < lnast.size(); i++)
	{
		for (int j = 1; j < lnast[i].size(); j++)
		{
			//____________________________________________________
			if (j == 1) //wyszukiwanie powtorzen aby uzupelniac prawa kolumne
			{
				for (int l = 0; l <= i; l++)
				{
					if (graf[lnast[i][j] - 1][0] == graf[l][1])
					{
						graf[l][1] = graf[lnast[i][0] - 1][1];
					}
				}
			}
			graf[lnast[i][j] - 1][0] = graf[lnast[i][0] - 1][1]; //przypisuje grot wektora do poczatku kolejnego
		}
	}
	//cout << "gotowy1" << endl;
	//Wypisz_graf();
	Uporzadkuj();

}
void Zapisz_graf()
{
	fstream plik("graf_oryg.txt", ios::out);

	for (int i = 0; i < graf.size(); i++)
	{
		for (int j = 0; j < graf[i].size(); j++)
		{
			if (j == 0)
			{
				plik << ";" << endl;
			}
			if ((i==(graf.size()-1)) && (j == (graf[i].size() - 1)))
			{
				plik << graf[i][j];
				break;
			}
			plik << graf[i][j] << endl;
		}
	}
	plik.close();
}

int main()
{
	Wczytaj_graf();
	Wypisz_lnast();

	if (Poprawnosc_grafu())
		return 0;

	if (Sprawdz_sprzezenie())
	{
		cout << "graf jest sprzezony";
		if (Sprawdz_liniowy())
			cout << " i liniowy" << endl;
		else
			cout << ", ale nie jest liniowy" << endl;

		cout << endl << "Nacisnij przycisk, aby przeksztalcic" << endl;
		_getch();

		Przeksztalcenie();

		cout <<endl << endl;
		Wypisz_graf();
		Zapisz_graf();
	}
	else
		cout << "graf jest niesprzezony" << endl;

	cout << endl << endl << "3#koniec_programu[ENDx02334f44]" << endl << endl;
}

