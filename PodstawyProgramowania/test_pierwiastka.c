#include<stdio.h>
#include<math.h>

#define ACCURACY (1.e-5) // do przeprowadzania obliczeĹ i sprawdzenia dokĹadnoĹci wyniku

void main( void ) {
  
  double liczba;
  
  for(;;){
    
    printf("\nPodaj wartoĹÄ liczby dodatniej (-1 koĹczy program):\n");
    scanf("%lf",&liczba);
    
    if(liczba<0.0) break;
    
    double pierwiastek = 1.0;
    double temp;
    // obliczenia pierwiastka za pomocÄ wzoru Herona
    do{
      temp = pierwiastek;
      pierwiastek = 0.5 * (temp + liczba/temp);
      
      // sprawdzenie warunku wyjĹcia z pÄtli - bĹÄd wzglÄdny obliczania pierwiastka
    } while(fabs(pierwiastek*pierwiastek - liczba)/liczba > ACCURACY); 
    
    
    printf("\nliczba %20.15lf, zaĹoĹźona dokĹadnoĹÄ obliczania pierwiastka: %20.15lf\n", 
	   liczba, ACCURACY);
    printf("\tpierwiastek liczby: obliczony %20.15lf, dokĹadny %20.15lf\n", 
	   pierwiastek, sqrt(liczba));
    printf("\tbĹÄd bezwzglÄdny: %20.15lf, bĹÄd wzglÄdny: %20.15lf\n",
	   pierwiastek-sqrt(liczba), (pierwiastek-sqrt(liczba))/sqrt(liczba));
    
  }
}


// definicja funkcji + komentarze (z komentarzy moĹźna tworzyÄ dokumentacjÄ):

// funkcja oblicz_pierwiastek oblicza pierwiastek za pomocÄ wzoru Herona
//               dla dowolnej liczby podwĂłjnej precyzji wiÄkszej od zera
// wariant 1. funkcja zakĹada, Ĺźe argument jest nie mniejszy niĹź zero
// wariant 2. dla liczb mniejszych od zera funkcja zwraca kod bĹÄdu: -1
//   implementacja w kodzie, np.
//  if(arg<0){
//    // obsĹuga bĹÄdu wejĹcia, np.
//    return(-1.0); // wyjaĹnienie w dokumentacji
//  }


// wydruki kontrolne do sprawdzenia dziaĹania funkcji:

//  printf("aktualna obliczona wartoĹÄ, \tbĹÄd wzglÄdny kolejnych iteracji, \tbĹÄd wzgledny kwadratu\n"); 
//
//do{ ....
//
//    printf("wartoĹÄ %20.15lf, \tbĹÄd  %20.15lf,     bĹÄd kwadratu %20.15lf\n", 
//	   pierwiastek, fabs(pierwiastek - temp)/pierwiastek, 
//	   fabs(pierwiastek*pierwiastek - arg)/arg);
//
//    ....}