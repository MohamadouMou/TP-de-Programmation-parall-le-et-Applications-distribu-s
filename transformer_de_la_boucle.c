#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define ms 2

int main(int argc, char** argv) {

	int i,j,k,x,c;
	int matrix_a[ms][ms];
	int matrix_b[ms][ms];
	int matrix_c[ms][ms];
	int myrank, p;
	int NRPE;
	double starttime, endtime;
	MPI_Status status;
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	
	
	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	NRPE = ms / p;
	
	if(myrank == 0){
	
		//matrix_a
		printf("\nmatrix A\n");
		printf("--------\n");
		
		for(i=0; i<ms; ++i){
			for(j=0; j<ms; j++){
				matrix_a[i][j] = rand() % 10;
			}
		}
		
		for(i=0; i<ms; ++i){
			for(j=0; j<ms; j++){
				printf("%3d", matrix_a[i][j]);
			}
			printf("\n");
		}
		
		//matrix_b
		printf("\nmatrix B\n");
		printf("--------\n");
		
		for(i=0; i<ms; i++){
			for(j=0; j<ms; j++){
				matrix_b[i][j] = rand() % 10;
			}
		}
		
		for(i=0; i<ms; i++){
			for(j=0; j<ms; j++){
				printf("%3d", matrix_b[i][j]);
			}
			printf("\n");
		}
	}
	
	//broadcast Matrix B values to all process
	for(i=0; i<ms; i++){
		MPI_Bcast(matrix_b[i], ms*ms, MPI_INT, 0, MPI_COMM_WORLD);
	}
	printf("\n MATRIX B by process: %d\n", myrank);
	for(i=0; i<ms; i++){
		for(j=0; j<ms; j++){
			printf("%3d", matrix_b[j][j]);
		}
		printf("\n");
	}
	
	
	// End of Broadcast
	
	// sending of each row of Matrix A to all process
	
	for(i=0; i<p; i++){
		for(j=0; j<ms; j++){
			MPI_Send(&matrix_a[j], ms*NRPE, MPI_INT, i, 0, MPI_COMM_WORLD);
			NRPE++;
		}
	}
	// End of sending row of Matrix A per process
	
	// receving for each 
	MPI_Recv(matrix_a, ms*NRPE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

	//multiplication Area
	starttime = MPI_Wtime();
	
	/*----------------------------------------------------------------------------------------------------
	
					//Nous avons ici une dépendance de flux
					//	Write matrix_c[i][k] --> Read matrix_c[i][k]
					//	
					//ce qui nous a permis de transformer i en k 	
					et on constate que le temps est obtimisé
	------------------------------------------------------------------------------------------------------
	*/
	for(k=0; k<ms; k++){
		for(i=0; i<ms; i++){
			matrix_c[i][k] = 0;
			for(j=0; j<ms; j++){
				matrix_c[i][k]  += matrix_a[i][j] *matrix_b[j][k];
			}
		}
	}
	endtime = MPI_Wtime();
	MPI_Send(&matrix_c[i][k], ms*ms, MPI_INT, 0, 0, MPI_COMM_WORLD);
	//end of multiplication
	
	//Display area
	if(myrank == 0){
		printf("\nResult MATRIX C\n");
		printf("\n----------------\n");
		
		for(i=0; i<ms; i++){
			printf("\n");
			for(k=0; k<ms; k++){
				printf("%3d", matrix_c[i][k]);
			}
		}
		printf("\nPrallele time %f seconds\n",endtime - starttime);
	}
	printf("\n");
	
	
	//return 0;
	// Finalize the MPI environment.
	MPI_Finalize();
}
