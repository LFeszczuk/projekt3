#include "minimax.hpp"

using namespace std;

ostatniRuch ostatni_ruch; // do przekazania ostatniego ruchu do funkcji Wygrana

// Algorytm rekurencyjny MINIMAX

int minimax(char **tablica, char gracz)
{
    int m, minmax;

    //plansza(tablica);																				//debug

    // WYGRANA GRACZA (10 dla X - komputer, -10 dla O człowiek)

    if (Wygrana(tablica, gracz, wygrana_ilosc_znakow, true))
        return (gracz == 'X') ? 10 : -10;

    if (Remis(tablica, true))
        return 0;

    gracz = (gracz == 'X') ? 'O' : 'X';

    minmax = (gracz == 'O') ? 10 : -10;

    for (int w = 1; w <= rozmiar; w++)
    {
        for (int k = 1; k <= rozmiar; k++)
        {
            if (tablica[w][k] == ' ')
            {
                //cout << "\n minimax pętla " << "w = " << w  << " "  << "k = " << k << "\n";							//debug

                tablica[w][k] = gracz;

                m = minimax(tablica, gracz);

                tablica[w][k] = ' ';

                if (((gracz == 'O') && (m < minmax)) || ((gracz == 'X') && (m > minmax)))
                    minmax = m;

                cout << "gracz = " << gracz << "minmax = " << minmax << "\n";
            }
        }
    }

    return minmax;
}

//Algorytm MinMax z obcinaniem alfa beta

int minimaxAlfaBeta(char **tablica, int glebokosc, char gracz, int alfa, int beta)
{
    int m, minmax;

    // Wygrana bierzącego gracza

    if (Wygrana(tablica, gracz, wygrana_ilosc_znakow, true))
        return (gracz == 'X') ? 100 - glebokosc : -100 + glebokosc;

    //cout << "\n minimax Wygrana " << " gracz: " << gracz;														//debug
    //cout << "\n minimax Wygrana " << " gracz: " << ostatniruch.gracz << "\n";									//debug

    // Remis

    if (Remis(tablica, true))
        return 0;

    //cout << "\n minimax remis\n";																				//debug

    // Analiza możliwych posunięć, zmiana gracza na przeciwnika

    gracz = (gracz == 'X') ? 'O' : 'X';

    //cout << "\n minimax zmiana gracza na:  " << gracz << "\n";												//debug

    minmax = (gracz == 'O') ? 100 : -100;

    if (gracz == 'X')
    {
        minmax = MIN;

        for (int w = 1; w <= rozmiar; w++)
        {
            for (int k = 1; k <= rozmiar; k++)
            {
                if (tablica[w][k] == ' ')
                {
                    //cout <<  \n" << w  << " "  << k << "\n";															//debug

                    tablica[w][k] = gracz;

                    m = minimaxAlfaBeta(tablica, glebokosc + 1, gracz, alfa, beta);

                    minmax = max(minmax, m);

                    alfa = max(alfa, minmax);

                    tablica[w][k] = ' ';

                    //cout << "gracz = " << gracz << "minmax = " << minmax << "\n";										//debug

                    if (beta <= alfa)
                        break;
                }
            }
        }

        return minmax;
    }

    if (gracz == 'O')
    {
        minmax = MAX;

        for (int w = 1; w <= rozmiar; w++)
        {
            for (int k = 1; k <= rozmiar; k++)
            {
                if (tablica[w][k] == ' ')
                {
                    //cout << "\n minimaxAlfaBeta \n" << w  << " "  << k << "\n";										//debug

                    tablica[w][k] = gracz;

                    m = minimaxAlfaBeta(tablica, glebokosc + 1, gracz, alfa, beta);

                    minmax = min(minmax, m);

                    beta = min(beta, minmax);

                    tablica[w][k] = ' ';

                    //cout << "gracz = " << gracz << "minmax = " << minmax <<  "\n";									//debug

                    if (beta <= alfa)
                        break;
                }
            }
        }

        return minmax;
    }

    return minmax;
}

// Funkcja wyznacza ruch dla komputera

Ruch komputer(char **tablica)
{
    int m, minmax;
    Ruch najRuch;
    najRuch.wiersz = -1;
    najRuch.kol = -1;

    minmax = -10;

    for (int w = 1; w <= rozmiar; w++)
    {
        for (int k = 1; k <= rozmiar; k++)
        {
            if (tablica[w][k] == ' ')
            {
                tablica[w][k] = 'X';

                //cout << "\n " << "w = " << w << "k = " << k << "\n";										//debug

                m = minimaxAlfaBeta(tablica, 0, 'X', MIN, MAX);

                //m = minimax(tablica, 'X');

                //cout << "\n " << "w = " << w << "k = " << k << "\n";										//debug

                //cout << "\n Ruch komputera " << "m = " << m << "\n";										//debug

                tablica[w][k] = ' ';

                if (m > minmax)
                {
                    minmax = m;
                    najRuch.wiersz = w;
                    najRuch.kol = k;
                }
            }
        }
    }

    return najRuch;
}

// Funkcja umożliwiająca ruchy graczy
void ruchyDwochGraczy(char **tablica, char &gracz)
{
    int w, k;

    int prawidlowy_ruch = 0; // prawidłowy ruch 0 - nie, 1 - tak

    cout << "Pierwszy gracz: O \n"
            "Drugi gracz: X \n";

    Wyswietl(tablica);
    if (gracz == 'O')
    {
        while (!prawidlowy_ruch)
        {
            cout << endl
                 << endl
                 << "GRACZ NR 1: O" << endl
                 << endl;
            cout << "Wybierz ruch  " << endl;

            cout << "Podaj wiersz: ";
            cin >> w;

            cout << endl
                 << "Podaj kolumnę: ";
            cin >> k;
            cout << endl;

            if ((w >= 1) && (w <= rozmiar) && (k >= 1) && (k <= rozmiar) && (tablica[w][k] == ' '))
            {
                cout << "Wstawiam:" << endl;
                tablica[w][k] = gracz;
                prawidlowy_ruch = 1;
            }
            else
                cout << "Pole jest już zajęte lub nie jest prawidłowe" << endl;
        }

        ostatni_ruch.wiersz = w;
        ostatni_ruch.kol = k;
        ostatni_ruch.gracz = gracz;
        cout << " Wiersz: " << ostatni_ruch.wiersz << " | Kolumna: " << ostatni_ruch.kol << " | Ruch gracza: " << ostatni_ruch.gracz << "\n";
    }
    else
    {
        while (!prawidlowy_ruch)
        {
            cout << endl
                 << endl
                 << "GRACZ NR 2: X" << endl
                 << endl;
            cout << "Wybierz ruch  " << endl;

            cout << "Podaj wiersz: ";
            cin >> w;

            cout << endl
                 << "Podaj kolumnę: ";
            cin >> k;
            cout << endl;

            if ((w >= 1) && (w <= rozmiar) && (k >= 1) && (k <= rozmiar) && (tablica[w][k] == ' '))
            {
                cout << "Wstawiam:" << endl;
                tablica[w][k] = gracz;
                prawidlowy_ruch = 1;
            }
            else
                cout << "Pole jest już zajęte lub nie jest prawidłowe" << endl;
        }

        ostatni_ruch.wiersz = w;
        ostatni_ruch.kol = k;
        ostatni_ruch.gracz = gracz;
        cout << " Wiersz: " << ostatni_ruch.wiersz << " | Kolumna: " << ostatni_ruch.kol << " | Ruch gracza: " << ostatni_ruch.gracz << "\n";
    }

    cout << endl
         << "---------------------------------------------" << endl
         << endl;

    gracz = (gracz == 'O') ? 'X' : 'O'; // zmiana gracza
}

// Funkcja umożliwiająca ruch gracza i komputera

void ruchyCzlowiekaZKomputerem(char **tablica, char &gracz)
{
    int w, k;
    Ruch ruch_komputera;
    int prawidlowy_ruch = 0; // prawidłowy ruch 0 - nie, 1 - tak

    Wyswietl(tablica);
    if (gracz == 'O')
    {
        while (!prawidlowy_ruch)
        {
            cout << endl
                 << endl
                 << "CZŁOWIEK: O" << endl
                 << endl;
            cout << "Wybierz ruch  " << endl;

            cout << "Podaj wiersz: ";
            cin >> w;

            cout << endl
                 << "Podaj kolumnę: ";
            cin >> k;
            cout << endl;

            if ((w >= 1) && (w <= rozmiar) && (k >= 1) && (k <= rozmiar) && (tablica[w][k] == ' '))
            {
                cout << "Wstawiam:" << endl;
                tablica[w][k] = gracz;
                prawidlowy_ruch = 1;
            }
            else
                cout << "Pole jest już zajęte lub nie jest prawidłowe" << endl;
        }

        ostatni_ruch.wiersz = w;
        ostatni_ruch.kol = k;
        ostatni_ruch.gracz = gracz;
        cout << " Wiersz: " << ostatni_ruch.wiersz << " | Kolumna: " << ostatni_ruch.kol << " | Ruch gracza: " << ostatni_ruch.gracz << "\n";
    }
    else // ruch komputera
    {
        cout << "\n Komputer myśli... \n"; //debug

        ruch_komputera = komputer(tablica);

        cout << endl
             << endl
             << "KOMPUTER: X" << endl
             << endl;
        cout << "Wybiera ruch:" << endl;

        //cout << ruch_komputera.wiersz << " " << ruch_komputera.kol << endl;										//debug

        tablica[ruch_komputera.wiersz][ruch_komputera.kol] = gracz;

        ostatni_ruch.wiersz = ruch_komputera.wiersz;

        ostatni_ruch.kol = ruch_komputera.kol;
        ostatni_ruch.gracz = gracz;

        cout << " Wiersz: " << ostatni_ruch.wiersz << " | Kolumna: " << ostatni_ruch.kol << " | Ruch gracza: " << ostatni_ruch.gracz << endl; //debug
    }

    cout << endl
         << "---------------------------------------------" << endl
         << endl;

    gracz = (gracz == 'O') ? 'X' : 'O'; // zmiana gracza
}
