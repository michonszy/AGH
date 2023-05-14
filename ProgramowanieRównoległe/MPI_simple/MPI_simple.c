#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"




#include <unistd.h>
#include <limits.h>

int main( int argc, char** argv ){ 


//char hostname[HOST_NAME_MAX + 1];
//  gethostname(hostname, HOST_NAME_MAX + 1);

//  printf("hostname: %s\n", hostname);

char address[256];
int lenght;

char buffer[512];


int rank, ranksent, size, source, dest, tag, i; 
char n;  
MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  gethostname(&address,256);
//	size=5;  
  if(size>1){
    
    if( rank != 0 ){ dest=0; tag=0; 
//      &address = &address + tag;

//int n;
sprintf(buffer,"Hostname: %s a watek to: %d",address,rank);
     printf("Wysylam hostname %s i id watka %d \n",address,tag);
    MPI_Send(buffer , 512, MPI_CHAR, dest, tag, MPI_COMM_WORLD );

      
    } else {
      
      for( i=1; i<size; i++ ) { 
	
	MPI_Recv(buffer,512, MPI_CHAR, MPI_ANY_SOURCE, 
		  MPI_ANY_TAG, MPI_COMM_WORLD, &status );
//sprintf("Dane otrzymane %s",ranksent);	
printf("Dane od procesu o randze (i=%d): %s (%d)\n", 
	       i,buffer, status.MPI_SOURCE);
      }
      
    }

  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

