#include <stdio.h>


void main( void ) // program kopiowania z stdin na stdout
{
  int c;
  c = getchar();
  while( (c = getchar()) != EOF) { 
  putchar(c); 
  }

  /*while (c != EOF) {
    putchar(c);
    c = getchar ();
  }*/
}

 //
