#include "backward.h"
#include <stdlib.h>

double **backward(HMM *hmm, const int *Y, const int T){
    
    unsigned int i;
    unsigned int j;
    
    // 2D beta matrix
    //
    // [state][time]
    //
    double **beta = calloc(hmm->hiddenStates, sizeof(double*));
    for(i = 0; i < hmm->hiddenStates; i++){
        beta[i] = calloc(T, sizeof(double));
    }
    
    // Initial setting the beta[T] values, these are said to be 1
    for(i = 0; i < hmm->hiddenStates; i++){
        beta[i][T-1] = 1;
    }
    
    // Now for the step"BACKWARD" step
    for(i = T-1; i-- >0;){
        for(j = 0; j < hmm->hiddenStates; j++){
            for(int l = 0; l < hmm->hiddenStates; l++){
                double emissionProb = hmm->emissionProbs[l][Y[i+1]];
                double transitionProb = hmm->transitionProbs[j][l];
                double oldBeta = beta[l][i+1];
                beta[j][i] += transitionProb*emissionProb*oldBeta;
            }
        }
    }
    
    
    printf("Backward\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < T; j++){
            printf("%f, ", beta[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    return beta;
    
}
