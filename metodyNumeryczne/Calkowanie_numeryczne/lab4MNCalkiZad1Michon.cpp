
#include <iostream>
#include<math.h>
using namespace std;


float fSinus(float x) {
    return sin(x);
}
float fExp(float x) {
    return exp(x);
}
float fx22x5(float x) {
    return x * x + 2 * x + 5;
}

void metoda_prostokatow(float a, float ak, float n, float(*funkcja)(float x) ){

    //SZYMON MICHOŃ
    cout <<endl<< "----- Metoda prostokatow -----" << endl;
     
    float skok = (ak - a) / n;
    //cout << "skok: " << skok << endl;
    float s = (ak - a) / n;
    float sumah = 0;

    float tab_h[4];
    //obliczenie h
    for (int i = 0; i < n; i++) {
        float x = a + skok * i;
        float pols = s / 2;
        float h = funkcja(x + pols);
        tab_h[i] = h;
    }
    //wypisanie h
    for (int i = 0; i < n; i++) {
        cout << "H" << i << " = " << tab_h[i] << endl;
        sumah = sumah + tab_h[i];
    }

    //obliczenie całki
    float calka = s * sumah;
    cout << "Calka to: " << calka << endl;

}

void metoda_trapezow(float a, float ak, float n, float(*funkcja)(float x)) {
    cout <<endl<< "----- Metoda trapezow -----" << endl;
    
    float skok = (ak - a) / n;
    //cout << "skok: " << skok << endl;
    float sumah = 0;

    float tab_h[4];
    //obliczenie h
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            a = a + skok;
        }
        else {
            a = a;
        }


        float b = a + skok;
        //cout << "a to: " << a << " b to: " << b << endl;
        float h = ((b - a) / 2) * (funkcja(a) + funkcja(b));
        tab_h[i] = h;
    }
    //wypisanie h
    for (int i = 0; i < n; i++) {
        cout << "H" << i << " = " << tab_h[i] << endl;
        sumah = sumah + tab_h[i];
    }

    //obliczenie całki
    float calka = sumah;
    cout << "Calka to: " << calka << endl;


}


void metoda_paraboli(float a, float ak, float n, float(*funkcja)(float x)) {
    cout <<endl<< " ----- Metoda Simpsona / paraboli -----" << endl;
    

    float sumah = 0;
    float skok = (ak - a) / n;
    //cout << "skok: " << skok << endl;
    float tab_h[4];
    //obliczenie h
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            a = a + skok;
        }
        else {
            a = a;
        }
        float b = a + skok;
        //cout << "a to: " << a << " b to: " << b << endl;
        float h = ((b - a) / 6) * (funkcja(a) + (4 * funkcja((a + b) / 2) )+ funkcja(b));
        tab_h[i] = h;
    }
    //wypisanie h
    for (int i = 0; i < n; i++) {
        cout << "H" << i << " = " << tab_h[i] << endl;
        sumah = sumah + tab_h[i];
    }

    //obliczenie całki
    float calka = sumah;
    cout << "Calka to: " << calka << endl;
}


int main()
{
    cout << endl << endl << " ---- 1 -----" << endl;
    metoda_prostokatow(0.5,2.5,4,fSinus);
    metoda_trapezow(0.5, 2.5, 4,fSinus);
    metoda_paraboli(0.5, 2.5, 4,fSinus);

    cout << endl << endl << " ---- 2 -----" << endl;
    metoda_prostokatow(0.5, 5, 4, fx22x5);
    metoda_trapezow(0.5, 5, 4, fx22x5);
    metoda_paraboli(0.5, 5, 4, fx22x5);

    cout << endl << endl << " ---- 3 -----" << endl;
    metoda_prostokatow(0.5, 5, 4, fExp);
    metoda_trapezow(0.5, 5, 4, fExp);
    metoda_paraboli(0.5, 5, 4, fExp);

   
}
