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
    
    for(i=0; i<hmm->observations; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            for(int q = 0; q < hmm->hiddenStates; q++){
                printf("%f, ", new_emission_probs[i][j*hmm->hiddenStates+q]);
            }
            printf("\n");
        }
        printf("\n\n");
    }
    
    double *newbeta = calloc(hmm->hiddenStates*T, sizeof(double));
    // Initial setting the beta[T] values, these are said to be 1
    for(i = 0; i < hmm->hiddenStates; i++){
        newbeta[i] = 1;
    }
    
    for(i = 1; i < T; i++){
        cblas_dgemv(CblasRowMajor, CblasNoTrans, hmm->hiddenStates, hmm->hiddenStates, 1.0, new_emission_probs[Y[i]], hmm->hiddenStates, newbeta+2*(i-1), 1, 0, newbeta+2*i, 1);
        printf("%f\n", scalingFactor[i]);
        //cblas_dscal(hmm->hiddenStates, scalingFactor[T-i], newbeta+2*i, 1);
    }
    

    for(i = 0; i < T; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            printf("%f, ", newbeta[i*hmm->hiddenStates+j]);
        }
        printf("\n");
    }
     
    
    // 2D beta matrix
    //
    // [state][time]
    //
    double *beta = calloc(hmm->hiddenStates*T, sizeof(double));
    // Initial setting the beta[T] values, these are said to be 1
    for(i = 0; i < hmm->hiddenStates; i++){
        beta[i*T+(T-1)] = 1;
    }
    
    // Now for the step"BACKWARD" step
    for(i = T-1; i-- >0;){
        for(j = 0; j < hmm->hiddenStates; j++){
            for(int l = 0; l < hmm->hiddenStates; l++){
                double emissionProb = hmm->emissionProbs[l*hmm->observations+Y[i+1]];
                double transitionProb = hmm->transitionProbs[j*hmm->hiddenStates+l];
                double oldBeta = beta[l*T+(i+1)];
                
                beta[j*T+i] += transitionProb*emissionProb*oldBeta;
            }
            beta[j*T+i] = beta[j*T+i] / scalingFactor[i+1];
        }
    }
    
    /*
     printf("Backward\n");
     for(i = 0; i < hmm->hiddenStates; i++) {
     for (j = 0; j < T; j++){
     printf("%f, ", beta[i*T+j]);
     }
     printf("\n");
     }
     printf("\n");
     */
    return beta;
    
}
