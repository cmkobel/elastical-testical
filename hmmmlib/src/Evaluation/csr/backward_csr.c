#include "backward_csr.h"
#include "forward_csr.h"
#include <stdlib.h>
#include <Accelerate/Accelerate.h> // for mac os
//#include <cblas.h> // for GNUlinux

void backward_csr(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * beta){

    unsigned int i;
    unsigned int j;
    
    //Creating the emission probs m*n into m, n*n matrix
    double ** new_emission_probs = calloc(hmm->observations, sizeof(double *));
    double * matrix = calloc(hmm->hiddenStates*hmm->hiddenStates, sizeof(double));
    
    for(i = 0; i < hmm->observations; i++){
        
        for(j = 0; j < hmm->hiddenStates; j++){
            matrix[j*hmm->hiddenStates+j] = hmm->emissionProbs[j*hmm->observations+i];
        }
        double * emission_probs = calloc(hmm->hiddenStates*hmm->hiddenStates, sizeof(double));
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, hmm->hiddenStates, hmm->hiddenStates, hmm->hiddenStates, 1.0, hmm->transitionProbs, hmm->hiddenStates, matrix, hmm->hiddenStates, 0.0, emission_probs, hmm->hiddenStates);
        new_emission_probs[i] = emission_probs;

    }
    
    free(matrix);
    
    for(i = 0; i < hmm->hiddenStates; i++){
        beta[hmm->hiddenStates*T-1-i] = 1;
    }
    
    int * ia = calloc(hmm->hiddenStates+1, sizeof(int));
    int * ja = calloc(hmm->hiddenStates*hmm->hiddenStates, sizeof(int));
    double * a = calloc(hmm->observations*hmm->hiddenStates*hmm->hiddenStates, sizeof(double));
    
    int znn = csr(hmm, new_emission_probs, ia, ja, a);
    
    for(i = 0; i < hmm->observations; i++){
        free(new_emission_probs[i]);
    }
    free(new_emission_probs);
    
//    printf("\nAI: \n");
//    for(i = 0; i < hmm->hiddenStates+1; i++){
//        printf("%d, ", ia[i]);
//    }
//    printf("\nJA: \n");
//    for(i = 0; i < hmm->hiddenStates*hmm->hiddenStates; i++){
//        if(a[i] == 0.0) break;
//        printf("%d, ", ja[i]);
//    }
//
//    printf("\n\n");
    
    for(i = 1; i<T; i++){
        for (int row=0; row < hmm->hiddenStates; row++) {
            double sum = 0.0;
            for(int idx=ia[row]; idx<ia[row+1]; idx++) {
                printf("%f, %f\n", beta[hmm->hiddenStates*(T-i)+ja[idx]], a[Y[T-i]*znn+idx]);
                sum += a[Y[T-i]*znn+idx] * beta[hmm->hiddenStates*(T-i)+ja[idx]];
            }
            beta[hmm->hiddenStates*(T-i)-hmm->hiddenStates+row] = sum;
        }
        cblas_dscal(hmm->hiddenStates, scalingFactor[T-i], beta+hmm->hiddenStates*T-i*hmm->hiddenStates-hmm->hiddenStates, 1);
        
        printf("BETA\n");
        for(int l = 0; l < T; l++){
            for(j = 0; j < hmm->hiddenStates; j++){
                printf("%f, ", beta[l*hmm->hiddenStates+j]);
            }
            printf("\n");
        }
        printf("\n");
        
    }
    
    free(ia);
    free(ja);
    free(a);

}

