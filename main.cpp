#include <fstream>
#include <iostream>
#include "gra.hpp"
#include "minimax.hpp"
using namespace std;
int wygrana_ilosc_znakow;
int main()
{
    cout << "wprowadz ilośc znaków w rzędzie do wygranej (więcej niż 3)" << endl;
    cin >> wygrana_ilosc_znakow;
    cout << "wprowadz rozmiar planszy (więcej niz 3) " << endl;
    cin >> rozmiar;
    char **tab;
    char gracz;

    tab = new char *[rozmiar + 1];
    int odp1, odp2;
    for (int i = 0; i < rozmiar + 1; i++)
        tab[i] = new char[rozmiar + 1];

    for (int i = 0; i <= rozmiar; i++)
    {
        for (int j = 0; j <= rozmiar; j++)
        {
            tab[i][j] = ' ';
        }
    }
    int wyborgry, wybor;
    for (;;)
    {
        cout << "Jaki tryb chcesz zagrać?" << endl;
        cout << "1. Ty i inny gracz" << endl;
        cout << "2. Ty i komputer" << endl;
        cout << "3. Koniec gry" << endl;
        cin >> wyborgry;
        switch (wyborgry)
        {
        case 1:
        {
            do
            {
                cout << "Gra w Kółko i Krzyżyk dla dwóch graczy\n"
                        "======================================"
                     << endl
                     << endl;

                // wyczyszczenie danych do planszy

                for (int i = 0; i <= rozmiar; i++)
                {
                    for (int j = 0; j <= rozmiar; j++)
                    {
                        tab[i][j] = ' ';
                    }
                }

                gracz = 'O';

                while (!Wygrana(tab, 'X', wygrana_ilosc_znakow, false) && !Wygrana(tab, 'O', wygrana_ilosc_znakow, false) && !Remis(tab, false))
                    ruchyDwochGraczy(tab, gracz);

                cout << "Jeszcze raz ? (T = TAK) (N = NIE): ";
                cin >> wybor;
                cout << "\n\n\n";

            } while ((wybor == 'T') || (wybor == 't'));

            if ((wybor == 'N') || (wybor == 'n'))
            {
                cout << "Koniec gry";

                // zwolnienie pamięci

                for (int i = 0; i < rozmiar + 1; i++)

                    delete[] tab[i];

                delete[] * tab;
                break;
            }
        }
        case 2:
        {
            do
            {
                cout << "Gra w Kółko i Krzyżyk dla gracza i komputera\n"
                        "============================================"
                     << endl
                     << endl;

                // wyczyszczenie danych do planszy

                for (int i = 0; i <= rozmiar; i++)
                {
                    for (int j = 0; j <= rozmiar; j++)
                    {
                        tab[i][j] = ' ';
                    }
                }

                gracz = 'X';

                while (!Wygrana(tab, 'X', wygrana_ilosc_znakow, false) && !Wygrana(tab, 'O', wygrana_ilosc_znakow, false) && !Remis(tab, false))
                    ruchyCzlowiekaZKomputerem(tab, gracz);

                cout << "Jeszcze raz ? (T = TAK) (N = NIE): ";
                cin >> wybor;
                cout << "\n\n\n";

            } while ((wybor == 'T') || (wybor == 't'));

            if ((wybor == 'N') || (wybor == 'n'))
            {
                cout << "Koniec gry";

                // zwolnienie pamięci

                for (int i = 0; i < rozmiar + 1; i++)

                    delete[] tab[i];

                delete[] * tab;

                break;
            }
        }
        case 3:
        {
            exit(0);
        }
        default:
        {
            cout << "nie ma takiej opcji" << endl;
            break;
        }
        }
    }
}