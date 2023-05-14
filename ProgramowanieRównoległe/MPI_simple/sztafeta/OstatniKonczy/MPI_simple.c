#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include "mpi.h"
int main(int argc, char** argv) {
//WERSJA PIERSCIENIA GDZIE OSTATNI PROCES KONCZY SZTAFETE
	int rank, ranksent, size, source, dest, tag, i;
	MPI_Status status;
//printf("Cos tam %d",status);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

//	printf("Metoda pierscienia gdzie proces %d zakonczy stafete",size);
//pierwszy przypadek
	 if( rank == 0 ){
printf("Metoda pierscienia gdzie proces %d zakonczy stafete \n",size-1);
		 dest=1;
		 tag=0;
	
		 MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
		 printf("Proces %d wyslal liczbe %d do procesu %d \n", rank, rank, dest);
		 	
	 } 
//ostatni przypadek
else if(rank == size-1){
		 	
		 dest=0;
		 tag=0;
	
		 MPI_Recv( &ranksent, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
		 printf("Proces %d odebral liczbe %d od procesu %d\n", rank, ranksent, status.MPI_SOURCE);
		 	
	 } 
//kazdy inny przypadek
else {
		 	
		 dest=rank+1;
		 tag=0;
		 	
		 MPI_Recv( &ranksent, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
		 printf("Proces %d odebral liczbe %d od procesu %d\n", rank, ranksent, status.MPI_SOURCE);
	
		 MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
		 printf("Proces %d wyslal liczbe %d do procesu %d\n", rank, rank, dest);
	 }

	MPI_Finalize();
	return(0);
}
