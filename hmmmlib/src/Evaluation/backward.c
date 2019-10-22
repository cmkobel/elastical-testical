#include "backward.h"
#include <stdlib.h>
#include <Accelerate/Accelerate.h>

double *backward(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor){
    
    unsigned int i;
    unsigned int j;
    
    //Creating the emission probs m*n into m, n*n matrix
    double ** new_emission_probs = calloc(hmm->observations, sizeof(double *));
    for(i = 0; i < hmm->observations; i++){
        double * matrix = calloc(hmm->hiddenStates*hmm->hiddenStates, sizeof(double));
        for(j = 0; j < hmm->hiddenStates; j++){
            matrix[j*hmm->hiddenStates+j] = hmm->emissionProbs[j*hmm->observations+i];
        }
        double * emission_probs = calloc(hmm->hiddenStates*hmm->hiddenStates, sizeof(double));
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, hmm->hiddenStates, hmm->hiddenStates, hmm->hiddenStates, 1.0, hmm->transitionProbs, hmm->hiddenStates, matrix, hmm->hiddenStates, 0.0, emission_probs, hmm->hiddenStates);
        new_emission_probs[i] = emission_probs;
    }
    
    double *beta = calloc(hmm->hiddenStates*T, sizeof(double));
    // Initial setting the beta[T] values, these are said to be 1
    for(i = 0; i < hmm->hiddenStates; i++){
        beta[i] = 1;
    }
    
    for(i = 1; i < T; i++){
        
        printf("New emission probs Y[i+1] = %d\n", Y[i+1]);
        for(int q = 0; q < hmm->hiddenStates; q++){
            for(int p = 0; p < hmm->hiddenStates; p++){
                printf("%f, ", new_emission_probs[Y[i+1]][q*hmm->hiddenStates+p]);
            }
            printf("\n");
        }
        printf("\n");
        
        cblas_dgemv(CblasRowMajor, CblasNoTrans, hmm->hiddenStates, hmm->hiddenStates, 1.0, new_emission_probs[Y[i+1]], hmm->hiddenStates, beta+hmm->hiddenStates*(i-1), 1, 0, beta+hmm->hiddenStates*i, 1);
        cblas_dscal(hmm->hiddenStates, scalingFactor[T-i], beta+hmm->hiddenStates*i, 1);
        
        for(j = 0; j < hmm->hiddenStates; j++){
            printf("%f, ", beta[i*hmm->hiddenStates+j]);
        }
        printf("\n");
    }
    
    
    printf("Backward\n");
    for(i = 0; i < T; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            printf("%f, ", beta[i*hmm->hiddenStates+j]);
        }
        printf("\n");
    }
    printf("\n");
    
    
    return beta;
    
}
