#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18

int main ()
{
  double a[WYMIAR];
//#OMP_NUM_THREADS; //zmienna definiująca liczbę wątków
#pragma omp  parallel for default(none) shared(a)
  for(int i=0;i<WYMIAR;i++) a[i]=1.02*i;

  // pętla sekwencyjna
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
      suma += a[i];
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  // pętla do modyfikacji - docelowo równoległa w OpenMP
  double suma_parallel=0.0;
  // ...

//zmienne do zadania 5
int porcja;

//#pragma omp parallel for //zadanie 4
//#pragma omp parallel for ordered //ordered do testow
porcja = 3;
#pragma omp parallel for schedule(static, porcja)
for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    // ...
      suma_parallel += a[i];
      // ...
//#pragma omp ordered
      printf("Static, porcja3, a[%2d]->W_%1d  \n",i,id_w); 
  }
printf("\nSuma wyrazów tablicy równolegle (z klauzulą - ....: %lf\n",
         suma_parallel);
suma_parallel=0;
//5.2
#pragma omp parallel for schedule(static)
for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    // ...
      suma_parallel += a[i];
      // ...
//#pragma omp ordered
      printf("Static, porcja def, a[%2d]->W_%1d  \n",i,id_w); 
  }
printf("\nSuma wyrazów tablicy równolegle (z klauzulą - ....: %lf\n",
         suma_parallel);
suma_parallel=0;
//5.3
int wateczki = omp_get_max_threads();
printf("Ilosc przydzielonych watkow: %d\n",wateczki);
porcja=2;
#pragma omp parallel for schedule(dynamic, porcja)
for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    // ...
      suma_parallel += a[i];
      // ...
//#pragma omp ordered
      printf("Dynamic, porcja 2, a[%2d]->W_%1d  \n",i,id_w); 
  }
printf("\nSuma wyrazów tablicy równolegle (z klauzulą - ....: %lf\n",
         suma_parallel);
suma_parallel=0;
//5.4
#pragma omp parallel for schedule(dynamic)
for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    // ...
      suma_parallel += a[i];
      // ...
//#pragma omp ordered
      printf("Dynamic, porcja def, a[%2d]->W_%1d  \n",i,id_w); 
  }

  printf("\nSuma wyrazów tablicy równolegle (z klauzulą - ....: %lf\n",
	 suma_parallel);

}
