#include <stdio.h>
#define ROZMIAR_TAB 4

int main()
{

 char tablica [ROZMIAR_TAB];
 int ndigit[ROZMIAR_TAB]={0};
 int i, nwhite=0, nother=0;

 
  for (int i = 0; i < ROZMIAR_TAB; i++) {
  tablica[i] = getchar();
  }

  fputs(tablica, stdout);
 

 for (int i = 0; i < ROZMIAR_TAB; i++){
 
    switch  (tablica [i]) {
    case 48: case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      ndigit[tablica[i]]++; 
      // printf("%c, %d,  %d\n", c, c-'0', ndigit[c-'0']); - wydruk kontrolny
      // (istnieją specjalne konstrukcje ułatwiające sprawdzanie na bieżąco
      // poprawności programu (np. assert, static_assert) )
      //break;
    case ' ': case '\n': case '\t': // znaki traktowane jako "white space"
      nwhite++;
      break;

     default:
      nother++;
      break;
     }
  }
  printf("\n digits:\n");  
  for (i = 0; i < nwhite; i++) printf("'%d' = %d\n", i, ndigit[i]);
  printf("white space = %d nother =  %d\n", nwhite, nother);
  return 0;
}


