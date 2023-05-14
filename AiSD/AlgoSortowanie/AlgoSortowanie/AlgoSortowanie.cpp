    // AlgoSortowanie.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
using namespace std;

float obliczanie(float a, float b, float c, float d) {
    float result;
    result = (a * (d * d)) + (b * d) + c;
    return result;
}

void quick_sort(float* tab, int lewy, int prawy)
{
    if (prawy <= lewy) return;

    int i = lewy - 1, j = prawy + 1,
        pivot = tab[(lewy + prawy) / 2];

    while (1)
    {

        while (pivot > tab[++i]);

        while (pivot < tab[--j]);

        if (i <= j)

            swap(tab[i], tab[j]);
        else
            break;
    }

    if (j > lewy)
        quick_sort(tab, lewy, j);
    if (i < prawy)
        quick_sort(tab, i, prawy);
}
int main()
{
    int SizeOfArray = 0;
    float a;
    float b;
    float c;
    float d;
    float x1;
    float x2;
    float x;

    
    cin >> SizeOfArray;

    float* tablicaArgumentow = new float[SizeOfArray];
    for (int i = 0; i < SizeOfArray; i++) {
        float x;
        cin >> x;
        tablicaArgumentow[i] = x;
    }
    cin >> a;
    cin >> b;
    cin >> c;

    float* tablicaWynikow = new float[SizeOfArray];
    for (int i = 0; i < SizeOfArray; i++) {
        float z = tablicaArgumentow[i];
        float x = obliczanie(a, b, c, z);
        tablicaWynikow[i] = x;
    }
    quick_sort(tablicaWynikow, 0, (SizeOfArray - 1));
    for (int i = 0; i < SizeOfArray; i++) {
        cout << tablicaWynikow[i] << " ";
    }
}
