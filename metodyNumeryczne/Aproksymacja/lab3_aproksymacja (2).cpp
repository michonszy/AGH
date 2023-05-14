//Szymon Michoń

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
int main()
{
    //zdefiniowanie tablicy
    float tab[8][2];
    tab[0][0] = 1; tab[0][1] = 2;
    tab[1][0] = 2; tab[1][1] = 4;
    tab[2][0] = 3; tab[2][1] = 3;
    tab[3][0] = 4; tab[3][1] = 5;
    tab[4][0] = 5; tab[4][1] = 6;
    tab[5][0] = 6; tab[5][1] = 9;
    tab[6][0] = 7; tab[6][1] = 11;
    tab[7][0] = 8; tab[7][1] = 11;

    //zdefiniowanie wartości, tutaj można dokonać zmian
    float m = 1;
    float macierz1[2][3];
    float x[2];
    
    //wartości dynamiczne
    float waga = 1;
    int rozm = m + 1;
    //wyliczenie g
    //float macierz1[rozm][rozm];
    
    cout << "Wyliczone g: " << endl;
        for (int j = 0; j < m+1; j++) {
            for (int k = 0; k < m+1; k++) {
                int g = 0;
                for (int x = 0; x < 8; x++) {
                    float liczba = tab[x][0];
                    float wynik = waga * pow(liczba, j)*pow(liczba,k);
                    g = g + wynik;
                }
                cout << g << " ";
                macierz1[j][k] = g;
            }
            
            cout << endl;
        }

        cout <<endl<< "Wyliczone f: " << endl;
    //wyliczanie f
        for (int j = 0; j < m+1; j++) {
            int g = 0;
            for (int x = 0; x < 8; x++) {
                float liczba = tab[x][0];
                float liczba2 = tab[x][1];
                float wynik = waga * pow(liczba, j)*liczba2;
                g = g + wynik;
            }
            cout << g << endl;
            macierz1[j][2] = g;
        }
        cout << "Przed przemiana: " << endl;
        for (int i = 0; i < rozm; i++) {
            for (int x = 0; x < rozm+1; x++) {
                cout << macierz1[i][x] << "   ";
            }
            cout << endl;

        }
      
        for (int k = 0; k < rozm; k++) {

            for (int w = k+1; w < rozm; w++) {
                float mnoznik;
                mnoznik = macierz1[w][k] / macierz1[k][k];
                //cout << "Mnoznik: " << mnoznik << endl;
                for (int x = 0; x < rozm+1; x++) {
                    macierz1[w][x] = macierz1[w][x] - (macierz1[k][x] * mnoznik);
                }
            }

            cout << "Po przemianie" << endl;
            for (int i = 0; i < rozm; i++) {
                for (int x = 0; x < rozm + 1; x++) {
                    cout << macierz1[i][x] << "   ";
                }
                cout << endl;

            }
        
        }

        /////DOTĄD KOD ZOSTAŁ NAPISANY I DZIAŁAŁ NA ZAJĘCIACH
        ////tutaj poprawiona częśc obliczania x
       
    //finalne obliczenia
       
        for (int i = rozm - 1; i >= 0; i--)
        {
            float x2;
            x2 = 0;
            for (int j = i + 1; j < rozm; j++)
                x2 += macierz1[i][j] * x[j];
            x[i] = (macierz1[i][rozm] - x2) / macierz1[i][i];
        }

        

        cout << endl<< "Obliczone wartosci x: " << endl;
        for (int i = 0; i < rozm; i++) {
            cout << x[i] << endl;
        }
            

        

    
        
        
     
}