#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10
#define NUM_THREADS 3 //dodana zmienna globalna dla 3 watkow

int main ()
{
  double a[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwójna pętla - sekwencyjnie
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);
//to jest w zad3 wymagane
  omp_set_nested(1);

//DEKOMPOZYCJA WIERSZOWA
  // podwójna pętla - docelowo równolegle
  double suma_parallel=0.0; int i,j;
  // poniżej dodana pętla zgodnie z wskazaniem, w reduction uzyskanie sumy, ilosc watkow w zmiennej globalnej schedule static rozmiar porcji 2
//musi byc ordered inaczej rzuca błędem
#pragma omp parallel for reduction(+:suma_parallel) num_threads(NUM_THREADS) schedule(static, 2) ordered
  for(i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    //suma_parallel += a[i][j];
#pragma omp ordered //odkomentowane
//DEKOMPOZYCJA KOLUMNOWA
    // podpunkt 2
#pragma omp parallel for reduction(+:suma_parallel) num_threads(NUM_THREADS) private(j) schedule(dynamic) ordered //dopisane
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
#pragma omp ordered //odkomentowane
      // dla dekompozycji 1D
      //printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
      // dla dekompozycji 2D
      printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
    }
#pragma omp ordered //odkomentowane
    printf("\n");
  }
printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);
suma_parallel=0;
//podpunkt 3 dekompozycja blokowana, zrównoleglenie obu pętli
//konieczne okazało się zdefiniowanie które zmienne mają być prywatne a które wspólne więc dodałem shared(suma_parallel, a) private(i, j) 
#pragma omp parallel default(none) shared(suma_parallel, a) private(i, j)  num_threads(NUM_THREADS)
    {
#pragma omp for ordered schedule(static)
        for (j = 0; j < WYMIAR; j++) {
            double suma_tmp = 0.0;
            for (i = 0; i < WYMIAR; i++) {
                suma_tmp += a[i][j];
#pragma omp ordered
                printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num());
            }

            suma_parallel += suma_tmp;
            printf("\n");
        }
    }
  printf("Suma wyrazów tablicy równolegle 2: %lf\n", suma_parallel);

}
