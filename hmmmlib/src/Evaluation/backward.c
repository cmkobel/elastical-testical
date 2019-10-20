#include "backward.h"
#include <stdlib.h>

double *backward(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor){
    
    unsigned int i;
    unsigned int j;
    
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
