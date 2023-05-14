#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

#define SCALAR double

#ifndef M_PI 
#define M_PI (3.14159265358979323846)
#endif

void main(int argc, char** argv){ // program obliczania przybliżenia PI za pomocą wzoru Leibniza
                                  // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
  //z z poprzednich zajec
	int rank, ranksent, size, source, dest, tag, i;
	MPI_Status status;
//printf("Cos tam %d",status);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

  int max_liczba_wyrazow = 0;

  if(rank == 0){
  	//z pliku oblicz_PI
    printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
    scanf("%d", &max_liczba_wyrazow);
  }
  // z wykładu W11
  MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

//musimy obliczyć jaki proces ma ile wyrazow pobrac i obliczyc
  int my_skok = ceil(max_liczba_wyrazow / size);

  int my_start = rank * my_skok;
  int my_end = my_start + my_skok - 1;


  double suma=0.0;

  //z pliku oblicz_PI
  SCALAR suma_plus=0.0;
  SCALAR suma_minus=0.0;

  for(i=my_start; i<=my_end; i++){
    
    int j = 1 + 4*i;
    
    suma_plus += 1.0/j;
    suma_minus += 1.0/(j+2.0);
    
   //printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
     //	 4*(suma_plus-suma_minus), 4.0/j-4.0/(j+2.0));
    
  }
  printf("Proces %d odebral liczbe %d od procesu %d\n", rank, ranksent, status.MPI_SOURCE);

  //to co finalnie ma zostać przekazane
  suma = suma_plus - suma_minus;


if(rank==0){
printf("PI obliczone: \t\t\t%20.15lf\n", 4*(suma_plus-suma_minus));
    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
}
  

  MPI_Finalize();


   
}