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




int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  gethostname(&address,256);
//	size=5;  
  if(size>1){
    
    if( rank != 0 ){ dest=0; tag=0; 
      
      MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
      
    } else {
      
      for( i=1; i<size; i++ ) { 
	
	MPI_Recv(&ranksent, 1, MPI_INT, MPI_ANY_SOURCE, 
		  MPI_ANY_TAG, MPI_COMM_WORLD, &status );
	printf("Dane od procesu o randze (i=%d): %d (%d) Hostname: %s\n", 
	       i,ranksent, status.MPI_SOURCE ,address);
      }
      
    }

  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

