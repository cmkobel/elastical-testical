#include "backward.h"
#include <stdlib.h>

double backward(HMM *hmm, const int *Y, const int T){
    
    unsigned int i;
    unsigned int j;
    
    double **beta = malloc(sizeof(double*)*hmm->hiddenStates);
    for(i = 0; i < hmm->hiddenStates; i++){
        beta[i] = malloc(sizeof(double)*T);
    }
    
    // Initial setting the beta[T] values, these are said to be 1
    for(i = 0; i < hmm->hiddenStates; i++){
        beta[i][T] = 1;
    }
    
    // Now for the step"BACKWARD" step
    
    
}
