#include "posteriorDecoding.h"
#include <stdlib.h>

double * posteriorDecoding(HMM * hmm, const unsigned int *Y, const unsigned int T){
    
    unsigned int i;
    unsigned int j;
    
    double * scalingFactor = calloc(T, sizeof(double));
    double * beta = calloc(T*hmm->hiddenStates, sizeof(double));
    double * alpha = calloc(hmm->hiddenStates*T, sizeof(double));
    
    forward(hmm, Y, T, scalingFactor, beta);
    backward(hmm, Y, T, scalingFactor, beta);

    double * z = calloc(T, sizeof(double));
    double posterior;
    
    for (i = 0; i < T; i++){
        posterior = -1.0;
        for (j = 0; j < hmm->hiddenStates; j++){
            if(alpha[i*T+j]*beta[i*T+j] > posterior){
                posterior = alpha[i*T+j]*beta[i*T+j];
            }
        }
        z[i] = posterior;
    }
    
    free(scalingFactor);
    free(alpha);
    free(beta);
    
    return z;
}
