#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include "mpi.h"
int main(int argc, char** argv) {

	int rank, ranksent, size, source, dest, tag, i;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	   
		if(size>1){
			if( rank == 0 ){
				dest=1;
				tag=0;

				MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
				printf("[proces %d] wyslal [%d] do [proces %d]\n", rank, rank, dest);
				
				MPI_Recv( &ranksent, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
				printf("[proces %d] odebral [%d] od [proces %d]\n", rank, ranksent, status.MPI_SOURCE);
			} else if(rank == size-1){
				
				dest=0;
				tag=0;

				MPI_Recv( &ranksent, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
				printf("[proces %d] odebral [%d] od [proces %d]\n", rank, ranksent, status.MPI_SOURCE);
				MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
				printf("[proces %d] wyslal [%d] do [proces %d]\n", rank, rank, dest);
			} else {
				
				dest = rank + 1;
				tag=0;
				MPI_Recv( &ranksent, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);
				printf("[proces %d] odebral [%d] od [proces %d]\n", rank, ranksent, status.MPI_SOURCE);
				MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
				printf("[proces %d] wyslal [%d] do [proces %d]\n", rank, rank, dest);
			}
		} else{
	   printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
		}

	MPI_Finalize();

	return(0);
}
