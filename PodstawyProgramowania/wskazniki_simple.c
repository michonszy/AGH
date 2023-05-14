#include <stdlib.h>
#include <stdio.h>

// deklaracja funkcji
void prosta_funkcja( void );

void main (void)
{

  int i = 1;
  
  int * wskaznik_do_int = &i; // wskazniki zawsze inicjowane przy definiowaniu  
  
  printf("\nprzed wywoĹaniem prostej funkcji\n"); 
  printf("\nwartoĹÄ zmiennej typu int i jej adres:    i = %d, &i = %lu \n", 
	 i, &i);
  printf("to samo co powyĹźej, za pomocÄ wskaĹşnikĂłw: i = %d, &i = %lu \n", 
	 *wskaznik_do_int, wskaznik_do_int);
  
  double pi = 3.14;
  double * double_p = NULL;
  printf("\nwartoĹÄ zmiennej pi: %lf, adres zmiennej pi: %lu\n", pi, &pi);
  printf("wskaĹşnik double_p zainicjowany wartoĹciÄ NULL:      %lu\n", double_p);
  double_p = &pi;
  printf("wskaĹşnik double_p po podstawieniu wartoĹci &pi:     %lu\n", double_p);
  
  // UWAGA: arytmetyka wskaĹşnikĂłw:
  double_p++;
  printf("wskaĹşnik double_p po wykonaniu operacji double_p++: %lu\n", double_p);
  // na co teraz pokazuje *double_p ????? - nie wiadomo,
  // co siÄ stanie gdy wykonanmy (*double_p)++ ????? - nie wiadomo, wiÄc...
  double_p--; // ...wracamy do poprzedniej wartoĹci &pi
  
  // wywoĹanie funkcji 
  prosta_funkcja();

  printf("\n\npo powrocie z prostej funkcji: \n");
  printf("wartoĹÄ zmiennej typu int i jej adres:    i = %d, &i = %lu \n", 
	 i, &i);
  printf("to samo co powyĹźej, za pomocÄ wskaĹşnikĂłw: i = %d, &i = %lu \n", 
	 *wskaznik_do_int, wskaznik_do_int);
  printf("\nwartoĹÄ zmiennej pi i jej adres:           pi = %lf, &pi = %lu\n", 
	 pi, &pi);
  printf("to samo co powyĹźej, za pomocÄ wskaĹşnikĂłw:  pi = %lf, &pi = %lu \n", 
	 *double_p, double_p);

}

void prosta_funkcja( void )
{

  printf("\n\nwewnÄtrz prostej funkcji: \n");

  return;
}