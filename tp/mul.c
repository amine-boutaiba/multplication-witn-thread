#include <time.h>
#include <stdlib.h>

#include "mul.h"
void mulMatrix (int **C, int **A,int **B,int n) {
int i, j,k;



for (i=0; i<n; i++){
     for (j=0; j<n; j++)
         {
          C[i][j]=0;
          for (k=0; k<n; k++){
               C[i][j] += A[i][k]*B[k][j];	    
		    
		    
}
}
}

}


