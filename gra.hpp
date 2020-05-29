#ifndef GRA_HPP_
#define GRA_HPP_

#include <iostream>

using namespace std;
#define MAX 100 // stałe do algorytmu minmax
#define MIN -100

extern int rozmiar; // extern bo zmienna globalna używana w gra i main

struct Ruch // do użycia w funkcji wyznaczającej ruch komputera
{
    int wiersz, kol;
};

struct ostatniRuch
{
    int wiersz, kol;
    char gracz;
};
void Wyswietl(char **tablica);
bool Wygrana(char **tablica, char gracz, int wygrana_ilosc_znakow, bool cisza);
bool Remis(char **tablica, bool cisza);

#endif