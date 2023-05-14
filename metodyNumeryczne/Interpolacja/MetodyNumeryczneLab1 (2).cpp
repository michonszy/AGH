#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    setlocale(LC_CTYPE, "Polish");
    int liczba_wezlow;
    float x0, x1, x2, x3;
    float f0, f1, f2, f3;
   
    int tablica[500];
    

    cout << "Zadanie Lab1 Szymon Michoń\n";

    //otwarcie pliku
    fstream plik;
    plik.open("FILES/MN-1-zad1-1.txt", ios::in | ios::out);
    
    //jeżeli istnieje zapisanie jego wartości do tablicy
    if (plik.good() == true)
    {
        int temp;
        for (int i = 0; i < 500 && plik >> temp; ++i) {
            tablica[i] = temp;
        }

    }
    //dane z tablicy zapisane do zmiennych
    liczba_wezlow = tablica[0];
    x0 = tablica[1];
    x1 = tablica[3];
    x2 = tablica[5];
    x3 = tablica[7];
    f0 = tablica[2];
    f1 = tablica[4];
    f2 = tablica[6];
    f3 = tablica[8];

    //wypisanie danych z pliku do konsoli
    cout << "Liczba węzłów: " << liczba_wezlow<<endl;
    cout << "Wezeł interpolacji 1 to: " << x0 << " a wartośc funkcji w węźle to: " << f0<< endl;
    cout << "Wezeł interpolacji 1 to: " << x1 << " a wartośc funkcji w węźle to: " << f1<< endl;
    cout << "Wezeł interpolacji 1 to: " << x2 << " a wartośc funkcji w węźle to: " << f2<< endl;
    cout << "Wezeł interpolacji 1 to: " << x3 << " a wartośc funkcji w węźle to: " << f3<< endl;


    ////wartość wielomianu interpolacyjnego Lagrangea
    cout << "Obliczanie wielomianu interpolacyjnego Lagrangea" << endl;
    float x;
    cout << "Podaj x: ";
    cin >> x;
    cout << "Punkt w którym liczymy wartość to: " << x << endl;

    float szukana = f0*(((x - x1)*(x - x2)*(x - x3)) / ((x0-x1)*(x0-x2)*(x0-x3)));
    float szukana2 = f1 * (((x - x0) * (x - x2) * (x - x3)) / ((x1 - x0) * (x1 - x2) * (x1 - x3)));
    float szukana3 = f2 * (((x - x0) * (x - x1) * (x - x3)) / ((x2 - x0) * (x2 - x1) * (x2 - x3)));
    float szukana4 = f3 * (((x - x0) * (x - x1) * (x - x2)) / ((x3 - x0) * (x3 - x1) * (x3 - x2)));

    float finalnie = szukana + szukana2 + szukana3 + szukana4;
    cout << "Wartośc wielomianu Lagrange'a w danym punkcie to: " << finalnie << endl;


    

    //otwarcie pliku
    fstream plik2;
    plik2.open("FILES/dane_wejsciowe_Newton.txt", ios::in | ios::out);
    float tablica2[100];

    //jeżeli istnieje zapisanie jego wartości do tablicy
    if (plik2.good() == true)
    {
        int temp;
        for (int i = 0; i < 500 && plik2 >> temp; ++i) {
            tablica2[i] = temp;
        }

    }

    
    int liczba = tablica2[0];

    float wartosci_funkcji[100];
    wartosci_funkcji[0] = tablica2[2];
    wartosci_funkcji[1] = tablica2[4];
    wartosci_funkcji[2] = tablica2[6];
    wartosci_funkcji[3] = tablica2[8];
    wartosci_funkcji[4] = tablica2[10];

    float wezl[100];
    wezl[0] = tablica2[1];
    wezl[1] = tablica2[3];
    wezl[2] = tablica2[5];
    wezl[3] = tablica2[7];
    wezl[4] = tablica2[9];

    //wartość Newtona
    //x1 nie może być równe xj
    //i nie może być równe j
    //rząd1
    float rzad1[100];
    float rzad2[100];
    float rzad3[100];
    float rzad4[100];

    cout << "Tablica ilorazów róźnicowych" << endl;
    cout << "Rzad1: ";
    for (int i = 0; i < liczba-1; i++) {
        float temp;
        float wynik = (wartosci_funkcji[i + 1] - wartosci_funkcji[i]) / (wezl[i + 1] - wezl[i]);
        rzad1[i] = wynik;
        cout << wynik << " ";
    }
    cout << endl;
    cout << "Rzad2: ";
    //rzad2
    for (int i = 0; i < liczba - 2; i++) {
        float temp;
        float wynik = (rzad1[i + 1] - rzad1[i]) / (wezl[i+2] - wezl[i]);
        rzad2[i] = wynik;
        cout << wynik << " ";
    }
    cout << endl;
    cout << "Rzad3: ";
    //rzad3
    for (int i = 0; i < liczba - 3; i++) {
        float temp;
        float wynik = (rzad2[i + 1] - rzad2[i]) / (wezl[i + 3] - wezl[i]);
        rzad3[i] = wynik;
        cout << wynik<<" ";
    }
    cout << endl;
    cout << "Rzad4: ";
    //rzad4
    for (int i = 0; i < liczba - 4; i++) {
        float temp;
        float wynik = (rzad3[i + 1] - rzad3[i]) / (wezl[i + 4] - wezl[i]);
        rzad4[i] = wynik;
        cout << wynik << " ";
    }
    cout << endl;
    
    //Wielomian interpolacyjny
    cout << "Wielomian interpolacyjny" << endl;
    cout << "Podaj punkt: ";
    
    cin >> x;
    cout << "Obliczam dla punktu: " << x << endl;
    
    float wielomian = wezl[0] + (rzad1[0] * (x - 1));
    float wielomian2 = 1 * ((x - 1) * (x - 2)) + 0 * ((x - 1) * (x - 2) * (x - 3)) + 0 * ((x - 1) * (x - 2) * (x - 3) * (x - 4));
    float wielomian_f = wielomian + wielomian2;
    cout << "Wartośc wielomianu Newtona w danym punkcie to: "<< wielomian_f << endl;

}