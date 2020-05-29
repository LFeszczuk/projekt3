#include "gra.hpp"
int rozmiar;
void Wyswietl(char **tablica)
{

    for (int i = 1; i <= rozmiar; i++)
    {
        for (int j = 1; j <= rozmiar; j++)
        {
            cout << " " << tablica[i][j] << " ";
            if (j < rozmiar)
                cout << "|";
            else if (i != rozmiar)
            {
                cout << "\n";
                for (int k = 1; k < rozmiar; k++)
                {
                    cout << "---+";
                }
                cout << "---\n";
            }
            else
                cout << "\n";
        }
    }
}

bool Wygrana(char **tablica, char gracz, int wygrana_ilosc_znakow, bool cisza)
{
    bool test;
    int tmp;

    test = false; // Zmienna przyjmuje true, jeśli gracz ma zadaną ilość znaków po kolei

    // sprawdzenie wierszy

    for (int w = 1; w <= rozmiar; w++)
    {
        for (int k = 1; k <= rozmiar + 1 - wygrana_ilosc_znakow; k++) // od pierwszej kolumny do ostaniej od której zmieści się zadana ilosc znaków po kolei
        {
            tmp = 0;

            for (int ilosc = 0; ilosc < wygrana_ilosc_znakow; ilosc++)
            {
                if (tablica[w][k + ilosc] == gracz)
                {
                    tmp = tmp + 1;
                }
            }

            if (tmp == wygrana_ilosc_znakow)
            {
                test = true;
            }
        }
    }

    // sprawdzenie kolumn

    for (int w = 1; w <= rozmiar + 1 - wygrana_ilosc_znakow; w++)
    {
        for (int k = 1; k <= rozmiar; k++)
        {
            tmp = 0;

            for (int ilosc = 0; ilosc < wygrana_ilosc_znakow; ilosc++)
            {
                if (tablica[w + ilosc][k] == gracz) // sprawdzanie w kolumnie
                {
                    tmp = tmp + 1;
                }
            }

            if (tmp == wygrana_ilosc_znakow)
            {
                test = true;
            }
        }
    }

    // sprawdzanie przekątnych "w prawo w dół"

    for (int w = 1; w <= rozmiar + 1 - wygrana_ilosc_znakow; w++)
    {
        for (int k = 1; k <= rozmiar + 1 - wygrana_ilosc_znakow; k++)
        {
            tmp = 0;

            for (int ilosc = 0; ilosc < wygrana_ilosc_znakow; ilosc++)
            {
                if (tablica[w + ilosc][k + ilosc] == gracz)
                {
                    tmp = tmp + 1;
                }
            }

            if (tmp == wygrana_ilosc_znakow)
            {
                test = true;
            }
        }
    }

    // sprawdzanie przekątnych "w lewo w dół"

    for (int w = 1; w <= rozmiar + 1 - wygrana_ilosc_znakow; w++)
    {
        for (int k = wygrana_ilosc_znakow; k <= rozmiar; k++)
        {
            tmp = 0;

            for (int ilosc = 0; ilosc < wygrana_ilosc_znakow; ilosc++)
            {
                if (tablica[w + ilosc][k - ilosc] == gracz)
                {
                    tmp = tmp + 1;
                }
            }

            if (tmp == wygrana_ilosc_znakow)
            {
                test = true;
            }
        }
    }

    // sprawdzanie przekątnych "w prawo w górę"

    for (int w = wygrana_ilosc_znakow; w <= rozmiar; w++)
    {
        for (int k = 1; k <= rozmiar + 1 - wygrana_ilosc_znakow; k++)
        {
            tmp = 0;

            for (int ilosc = 0; ilosc < wygrana_ilosc_znakow; ilosc++)
            {
                if (tablica[w - ilosc][k + ilosc] == gracz)
                {
                    tmp = tmp + 1;
                }
            }
            if (tmp == wygrana_ilosc_znakow)
            {
                test = true;
            }
        }
    }

    // sprawdzanie przekątnych "w lewo w górę"

    for (int w = wygrana_ilosc_znakow; w <= rozmiar; w++)
    {
        for (int k = wygrana_ilosc_znakow; k <= rozmiar; k++)
        {
            tmp = 0;

            for (int ilosc = 0; ilosc < wygrana_ilosc_znakow; ilosc++)
            {
                if (tablica[w - ilosc][k - ilosc] == gracz)
                {
                    tmp = tmp + 1;
                }
            }
            if (tmp == wygrana_ilosc_znakow)
            {
                test = true;
            }
        }
    }

    if (test)
    {
        if (!cisza)
        {
            Wyswietl(tablica);
            cout << "\nGRACZ " << gracz << " WYGRYWA!!!\n\n";
        }

        return true;
    }

    return false;
}

// Funkcja zwraca true, jeśli już nie ma możliwości ruchu na planszy

bool Remis(char **tablica, bool cisza)
{
    // Plansza posiada wolne pola (spacje)
    for (int i = 1; i <= rozmiar; i++)
    {
        for (int j = 1; j <= rozmiar; j++)
        {
            if (tablica[i][j] == ' ')
                return false;
        }
    }

    // Pętla for zakończyła sie normalnie (brak spacji) - REMIS

    if (!cisza)
    {
        Wyswietl(tablica);
        cout << "\nREMIS\n\n";
    }

    return true;
}