#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>



#include "initMatrix.h"
#include "displayMatrix.h"
#include "mul.h"
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


clock_t   tdebut,tfin,s_debut,s_fin;
int ver;
double p_temps,s_temps,t_acceleration,temps ;
void multiplication_matrix_thread(void * args);

int main(int argc, char **argv) {

	int n;  	// MATRIX DIMENSION
	int i, j;

	if (argc == 1){
		printf("Usage: ./app-hw1 <matrix-size>\n");
		return 1;
	}
      
        char *    Mode      =  argv[1];
	n = atoi (argv[2]);
	int  nombrethread =  atoi (argv[3]);
	
	
	struct matrice Arg;
	Arg.nombrethread = nombrethread ;
	Arg.n = n;
	Arg.bloc_calcul_thread = n/nombrethread;
	Arg.reste = n%(nombrethread/2);
	Arg.idebut = 0;
	
	Arg.ifin = n-1;
	Arg.jdebut = 0;
	
	Arg.jfin = n-1;
	
	printf("Matrix size = %d\n", n);
	int **A = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		A[i] = (int *)malloc(n * sizeof(int));
// genere la matrice A ar la fct rand
        generateRandomMatrix(A, n, 0, 99);
//affichage de la matrice A	
	printMatrix(A, n);

	
	
printf("\n");
	
printf("Matrix 2 size = %d\n", n);
	int **B = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		B[i] = (int *)malloc(n * sizeof(int));
// genere la matrice A ar la fct rand
	generateRandomMatrix(B, n, 1, 99);
// affichage de la matrice B	
	printMatrix(B, n);
// la matrice resutat de la mult	
	int **C = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		C[i] = (int *)malloc(n * sizeof(int));
// la matrice VERIIFCATION 	
	int **D = (int **)malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		D[i] = (int *)malloc(n * sizeof(int));
s_debut=clock();

mulMatrix(D,A,B,n);// mettre le resulta de la multiplication en sequential 

s_fin=clock();

temps=((double)s_fin-s_debut)/CLOCKS_PER_SEC; // se temps pour compare le temps de accelaration avec le temps parallele

       //  Creation des threads
	
	Arg.A = A;
	Arg.B = B;
	Arg.C = C;
       
       
      if((!strcmp(Mode,"S"))||(!strcmp(Mode,"s"))){
      
		printf("Le resultat de notre matrice Sequential  : \n");
               tdebut=clock();
		mulMatrix(C,A,B,n);
		tfin=clock();
		
		printMatrix(C, n);
		  s_temps = ((double)tfin - tdebut) / CLOCKS_PER_SEC;
		 printf("le temps d execution en sequential est :%f\t \n",s_temps);
		}
      
	
	else if ((!strcmp(Mode,"P"))||(!strcmp(Mode,"p"))){ 

		printf(" Le resultat de notre matrice Parallel  : \n");
	

	
		pthread_t *threads = (pthread_t*) malloc(sizeof(pthread_t) *nombrethread );
		
	
		for(i=0; i<nombrethread; i++){ 
		Arg.idebut=i*(nombrethread/2);
		Arg.ifin=Arg.idebut+(nombrethread/2)+Arg.reste;
		Arg.jdebut = j * (n/(nombrethread/2));
	        Arg.jfin = Arg.jdebut + (n/(nombrethread/2))-1+Arg.reste ;
		tdebut=clock();
		pthread_create(&threads[i], NULL,multiplication_matrix_thread,&Arg);
	
		pthread_join(threads[i], NULL);
		tfin=clock();
		p_temps = ((double)tfin - tdebut) / CLOCKS_PER_SEC;
		 
		}
		printMatrix(C, n);
    
 printf("le temps d execution en parallel est %f:\t \n",p_temps);


//cele pour verifie si la matrcie calcule en parrallel a le meme resultat avec matrice en sequential 
 ver=0;
 for (i=0;i<n;i++){
    	for (j=0;j<n;j++){
        	 ver=ver+C[i][j]-D[i][j];
    		   }
    	        	  }
    if(ver==0){
    }else { // si on affichage d un msg de erreur
    printf("Notre resulta n'est pas vrai");
    }				
 ///////////////////////////////////////////////////////////////////////////////////////////////////		
}
// le temps d accelaration 

t_acceleration=temps/p_temps;
 printf("\nle temps d'accelration  est %f:\t \n",t_acceleration);


}
