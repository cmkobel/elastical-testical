#include "posteriorDecoding.h"
#include <stdlib.h>

double * posteriorDecoding(HMM * hmm, const int *Y, const int T){
    
    unsigned int i;
    unsigned int j;
    
    double * scalingFactor = calloc(T, sizeof(double));
    double * alpha = forward(hmm, Y, T, scalingFactor);
    double * beta = backward(hmm, Y, T, scalingFactor);

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
