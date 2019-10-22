#include "forward.h"
#include <stdlib.h>
#include <Accelerate/Accelerate.h>

double * forward(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor){
    
    unsigned int i;
    unsigned int j;
    
    //Creating the emission probs m*n into m, n*n matrix
    double ** new_emission_probs = calloc(hmm->observations, sizeof(double *));
    for(i = 0; i < hmm->observations; i++){
        double * matrix = calloc(hmm->hiddenStates*hmm->hiddenStates, sizeof(double));
        for(j = 0; j < hmm->hiddenStates; j++){
            matrix[j*hmm->hiddenStates+j] = hmm->emissionProbs[j*hmm->observations+i];
        }
        new_emission_probs[i] = matrix;
    }
    
    double * alpha = calloc(hmm->hiddenStates*T, sizeof(double));
    
    // Doing the matrix multiplication and then scalingFactor
    cblas_dsymv(CblasRowMajor, 121, hmm->hiddenStates, 1.0, new_emission_probs[Y[0]], hmm->hiddenStates, hmm->initProbs, 1, 1, alpha, 1);
    scalingFactor[0] = cblas_dasum(hmm->hiddenStates, alpha, 1);
    cblas_dscal(hmm->hiddenStates, (1.0/scalingFactor[0]), alpha, 1);
    
    for(i = 1; i<T; i++){
        cblas_dgemv(CblasRowMajor, CblasTrans, hmm->hiddenStates, hmm->hiddenStates, 1.0, hmm->transitionProbs, hmm->hiddenStates, alpha+hmm->hiddenStates*(i-1), 1, 0, alpha+hmm->hiddenStates*i, 1);
        cblas_dgemv(CblasRowMajor, CblasTrans, hmm->hiddenStates, hmm->hiddenStates, 1.0, new_emission_probs[Y[i]], hmm->hiddenStates, alpha+hmm->hiddenStates*i, 1, 0, alpha+hmm->hiddenStates*i, 1);
        scalingFactor[i] = 1.0/cblas_dasum(hmm->hiddenStates, alpha+hmm->hiddenStates*i, 1);
        cblas_dscal(hmm->hiddenStates, scalingFactor[i], alpha+hmm->hiddenStates*i, 1);
    }
    
    printf("Forward\n");
    for(i = 0; i < T; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            printf("%f, ", alpha[i*hmm->hiddenStates+j]);
        }
        printf("\n");
    }
    printf("\n");
    return alpha;
}
