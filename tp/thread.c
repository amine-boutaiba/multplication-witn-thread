#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "thread.h"

struct matrice{
int **A;
int **B;
int **C;
int n;
int nombrethread;
int bloc_calcul_thread;
int reste;
int idebut;
int ifin;

int jdebut;
int jfin;

};



void multiplication_matrix_thread(void * args){
struct matrice * matricee;
matricee=(struct matrice *)args;
for(int i=matricee->idebut;i<=matricee->ifin;i++){
for(int j=matricee->jdebut; j<matricee->jfin; j++){
matricee->C[i][j]=0;
for(int k=0; k<matricee->n; k++){
matricee->C[i][j] =matricee->C[i][j]+ matricee->A[i][k] * matricee->B[k][j];			
}
}	
}

}

