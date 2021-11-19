#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ms 2

int main(int argc, char** argv) {

	int i,j,k,x,c;
	int matrix_a[ms][ms];
	int matrix_b[ms][ms];
	int matrix_c[ms][ms];
	
	clock_t debut, fin;

	
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
	
	
	
	

	//multiplication Area
	debut = clock();
	
	for(k=0; k<ms; k++){
		for(i=0; i<ms; i++){
			matrix_c[i][k] = 0;
			for(j=0; j<ms; j++){
				matrix_c[i][k]  += matrix_a[i][j] *matrix_b[j][k];
			}
		}
	}
	fin = clock();
	
	//end of multiplication
	
	//Display area
	
		printf("\nResult MATRIX C\n");
		printf("\n----------------\n");
		
		for(i=0; i<ms; i++){
			printf("\n");
			for(k=0; k<ms; k++){
				printf("%3d", matrix_c[i][k]);
			}
		}
		printf("le temps d'execution de ce processus est %f secondes\n",(double)fin - debut);
	
	printf("\n");
	
	
	return 0;
	
}
