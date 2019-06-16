// AKwB_4.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <time.h>

using namespace std;

//Do odczytu
string multizbior = "multi1.txt";

vector<int> multi;
vector<int> rozw;
vector<int> zuzyte;
vector<int> testy;

int maxind;

clock_t start, koniec;
double czas;



//Funkcje
void artificial_map()
{
	int a = 6;
	int map[] = { 76, 20, 35, 15, 4, 10 };

	int k = 0;																	//
	for (int i = 0; i < a; i++)
	{
		multi.push_back(map[i]);

		k += map[i];
		if (i != 0) {
			multi.push_back(k);

			int sum = 0;
			for (int j = i; j < a; j++)
			{
				sum += map[j];
				if (j != i) {
					multi.push_back(sum);
				}
			}
		}
	}
	sort(multi.begin(), multi.end());
	fstream tenmulti;
	tenmulti.open(multizbior.c_str(), ios::out);
	if (tenmulti.good())
	{
		for (int i = 0; i < multi.size(); i++)
		{
			tenmulti << multi[i] << " ";
		}
	}
	tenmulti.close();
}
void Wczytaj()
{
	fstream tenmulti;

	int liczba;

	tenmulti.open(multizbior.c_str(), ios::in);
	if (tenmulti.good())
	{
		while (!tenmulti.eof())
		{
			tenmulti >> liczba;
			multi.push_back(liczba);
			cout << liczba << " ";
			//_getch();
		}
	}
	sort(multi.begin(), multi.end());
	tenmulti.close();
}
void Wypisz_multi()
{
	for (int i = 0; i < multi.size(); i++)
	{
		cout << multi[i] << " ";
	}
	cout << endl << endl;
}
int Licznosc_zbioru()
{
	for (int i = 1; i < multi.size(); i++)
	{
		int a = ((i * (i - 1)) / 2);
		if (a == multi.size())
			return i;
		if (a > multi.size())
		{
			cout << endl << "Blad w multizbiorze :(" << endl;
			return 0;
		}
	}
}
void wypisz_zuzyte()
{
	cout << endl << "zuzyte" << endl;
	for (int i = 0; i < zuzyte.size(); i++)
	{
		cout << zuzyte[i] << " ";
	}
}
void wypisz_rozw()
{
	cout << endl << "rozw" << endl;
	for (int i = 0; i < rozw.size(); i++)
	{
		cout << rozw[i] << " ";
	}
}
void szukaj(int ind, int *jest)
{
	bool dobra = false;

	for (int i = 0; i < zuzyte.size(); i++)
		zuzyte[i] = 0;

	for (int i = 0; i < rozw.size(); i++)
	{
		for (int j = 0; j < multi.size(); j++)
		{
			if (rozw[i] == multi[j])
			{
				if (zuzyte[j] == 1) {
					continue;
				}
				else {
					zuzyte[j] = 1;
					break;
				}
			}
		}
	}
	if (ind - 1 == maxind)
	{
		bool znalezione = true;
		
		vector<int> testy;

		int k = 0;
		for (int i = 0; i < rozw.size(); i++)
		{
			testy.push_back(rozw[i]);

			k += rozw[i];
			if (i != 0) {
				testy.push_back(k);

				int sum = 0;
				for (int j = i; j < rozw.size(); j++)
				{
					sum += rozw[j];
					if (j != i) {
						testy.push_back(sum);
					}
				}
			}
		}
		sort(testy.begin(), testy.end());

		if (testy.size() == multi.size())
		{
			for (int i = 0; i < testy.size(); i++)
			{
				if (multi[i] != testy[i])
				{
					znalezione = false;
					break;
				}
			}
		}
		else
			znalezione = false;

		if (znalezione)
		{
			cout << endl << endl << "znalezona mapa restrykcyjna: " << endl << "( ";
			for (int i = 0; i < rozw.size(); i++)
			{
				cout << rozw[i] << ", ";
			}
			cout << ")" << endl << endl;
			fstream tenmulti;
			tenmulti.open(multizbior.c_str(), ios::app);
			if (tenmulti.good())
			{
				tenmulti << endl;
				for (int i = 0; i < rozw.size(); i++)
				{
					tenmulti << rozw[i] << " ";
				}
			}
			tenmulti.close();
			*jest = 1;
		}
		else
		{
			//cout << "1";
			int a = rozw[ind - 1];
			for (int i = 0; i < multi.size(); i++)
			{
				if (a == multi[i])
				{
					zuzyte[i] = 0;
					break;
				}
			}
		}

	}
	else
		for (int i = 0; i < multi.size(); i++)
		{
			//cout << "2";
			bool test;

			//wypisz_zuzyte();
			//wypisz_rozw();
			//_getch();


			if (zuzyte[i] == 0)
			{
				rozw[ind] = multi[i];

				for (int j = 0; j <= ind; j++)
				{
					int sum = 0;
					for (int l = j; l <= ind; l++)
					{
						sum += rozw[l];

						test = false;

						for (int m = 0; m < multi.size(); m++)
						{
							if (multi[m] == sum) {
								test = true;
							}
						}
						if (!test)
						{
							dobra = false; 
							rozw[ind] = 0;
							break;
						}
						else
							dobra = true;
					}
					if (!test)
						break;
				}
				if (dobra)
					szukaj(ind + 1, jest);
			}
			if (*jest == 1)
				break;
		}
}

int main()
{
	Wczytaj();
	//artificial_map();

	//cout << endl << "koniec";


	Wypisz_multi();
	//cout << multi.size();
	int k = Licznosc_zbioru() - 1;//5
	if (k < 0) {
		return 0;
	}
	cout << endl << "Licznosc zbioru: " << k << endl;
//_____________________________________________________________________________________________ 
	for (int i = 0; i < k; i++) //tworze odpowiednia ilosc zuzytych
		rozw.push_back(0);

	for (int i = 0; i < multi.size(); i++) //tworze odpowiednia ilosc zuzytych
		zuzyte.push_back(0);

	int first = multi[multi.size() - 1] - multi[multi.size() - 2];
	rozw[0] = first; // wrzucam pierwszy element mapy do rozw
	//cout << first; 

	int jest = 0;
	maxind = k - 1; //4


	start = clock();
	szukaj(1, &jest); //zaczynam poziom od 1 bo pierwszy element juz wrzucilem do vectora
	koniec = clock();

	czas = (double)(koniec - start) / (double)(CLOCKS_PER_SEC);
	cout << "\n czas trwania to: " << czas << endl;


	if (jest == 0)
	{
		cout << endl << " BRAK ROZWIAZANIA " << endl;
	}

	return 0;
}
