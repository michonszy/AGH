#include <iostream>
#include <fstream>
using namespace std;
int main()
{

    //otwarcie pliku
    fstream plik;
    plik.open("dane.txt", ios::in | ios::out);
    float tab [4][5];
    //jeżeli istnieje zapisanie jego wartości do tablicy
    if (plik.good() == true)
    {
        int temp;
        for (int i = 0; i < 4; i++) {
            for(int x=0;x<5 && plik>>temp;x++){
                tab[i][x] = temp;
            }

        }

    }
    //zdefiniowanie tablicy

//    tab[0][0] = 2;
//    tab[0][1] = 4;
//    tab[0][2] = 2;
//    tab[0][3] = 1;
//    tab[0][4] = 10;
//
//    tab[1][0] = 2;
//    tab[1][1] = 2;
//    tab[1][2] = 3;
//    tab[1][3] = 3;
//    tab[1][4] = 6;
//
//    tab[2][0] = 4;
//    tab[2][1] = 2;
//    tab[2][2] = 2;
//    tab[2][3] = 1;
//    tab[2][4] = 6;
//
//    tab[3][0] = 0;
//    tab[3][1] = 2;
//    tab[3][2] = 1;
//    tab[3][3] = 1;
//    tab[3][4] = 4;
    cout << "Początkowa tablica" << endl;
    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 5; x++) {
            cout << tab[i][x] << "   ";
        }
        cout << endl;

    }

    //int wynik1 [4][5];
    //obliczenie mnożnika
    // DZIAŁAJĄCY DLA 0 KOLUMNY
    //for (int i = 1; i < 4; i++) {
    //	//for (int z = 0; z < 4; z++) {
    //		int mnoznik;
    //		mnoznik = tab[i][0] / tab[0][0];
    //		for (int x = 0; x < 5; x++) {
    //			wynik1[i][x] = tab[i][x] - (tab[0][x] * mnoznik);
    //			cout << wynik1[i][x] << "   ";

    //		}
    //		cout << endl;
    //	//}

    //
    //}
    ////zadanie2
    //pivoting
    for(int i=0;i<3;i++)
    {
        if(tab[i][0]<tab[i+1][0]){
            for(int j=0;j<4;j++)
            {
                float c=tab[i][j];
                tab[i][j]=tab[i+1][j];
                tab[i+1][j]=c;
            }
        }

    }
    //koniec pivotingu

    for (int k = 0; k < 3; k++) {

        for (int w = k+1; w < 4; w++) {
            float mnoznik;
            mnoznik = tab[w][k] / tab[k][k];
            for (int x = 0; x < 5; x++) {
                tab[w][x] = tab[w][x] - (tab[k][x] * mnoznik);

            }



        }
//        cout << "Po przemianie" << endl;
//        for (int i = 0; i < 4; i++) {
//            for (int x = 0; x < 5; x++) {
//                cout << tab[i][x] << "   ";
//            }
//            cout << endl;
//
//        }
    }

    cout << "Po przemianie" << endl;
    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 5; x++) {
            cout << tab[i][x] << "   ";
        }
        cout << endl;

    }
//ETAP DRUGI
//obliczenie x0
    float x3 = tab[3][4] / tab[3][3];
    cout << "x3: " << x3 << endl;
    float x2 = (tab[2][4] - tab[2][3] * x3)/tab[2][2];
    cout << "x2: " << x2 << endl;
    float x1= (tab[1][4]-(tab[1][2]*x2+tab[1][3]*x3))/tab[1][1];
    cout<<"x1: "<<x1<<endl;
    float x0 = (tab[0][4]-(tab[0][1]*x1+(tab[0][2]*x2)+(tab[0][3]*x3)))/tab[0][0];
    cout<<"x0: "<<x0<<endl;
}
