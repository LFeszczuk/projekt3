#ifndef MINMAX_HPP_
#define MINMAX_HPP_

#include "gra.hpp"
#include <iostream>

extern int wygrana_ilosc_znakow;

int minimax(char **tablica, char gracz);
int minimaxAlfaBeta(char **tablica, int glebokosc, char gracz, int alfa, int beta);
Ruch komputer(char **tablica);
void ruchyCzlowiekaZKomputerem(char **tablica, char &gracz);
void ruchyDwochGraczy(char **tablica, char &gracz);

#endif