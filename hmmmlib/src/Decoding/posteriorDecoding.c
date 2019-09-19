#include "posteriorDecoding.h"
#include <stdlib.h>

int posteriorDecoding(HMM * hmm, const int *Y, const int T, const int t){
    
    int index = 0;
    unsigned int i;
    
    double * scalingFactor = calloc(T, sizeof(double));
    double * alpha = forward(hmm, Y, T, scalingFactor);
    double * beta = backward(hmm, Y, T, scalingFactor);
    
    double largest = 0.0;
    
    for (i = 0; i < hmm->hiddenStates; i++) {
        
        double gamma = alpha[i*T+t]*beta[i*T+t];
        
        if(gamma > largest){
            index = i;
            largest = gamma;
        }
    }
    
    free(scalingFactor);
    free(alpha);
    free(beta);
    
    return index;
}
