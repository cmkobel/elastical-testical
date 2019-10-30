#include "posteriorDecoding.h"
#include <stdlib.h>
#include <math.h>

double * posteriorDecoding(HMM * hmm, const int *Y, const int T){
    //                     hmm-obj    data          len(data)
    
    
    double * scalingFactor = calloc(T, sizeof(double));
    double * alpha = forward(hmm, Y, T, scalingFactor); // scalingFactor bliver sat her.
    double * beta = backward(hmm, Y, T, scalingFactor); // scalingFactor bliver brugt her.

    double * z = calloc(T, sizeof(double));
    //double posterior; // Skal posterior ikke være en liste?
    double * posterior = calloc(hmm->hiddenStates, sizeof(double));

    for (unsigned int i = 0; i < T; i++) {
        for (unsigned int k = 0; k < hmm->hiddenStates; k++){
            posterior[k] = alpha[i*T+k]*beta[i*T+k];
            /* if(alpha[i*T+k]*beta[i*T+k] > posterior){
                posterior = alpha[i*T+k]*beta[i*T+k];
            } */
        }
        //z[i] = posterior; # men det skal jo være max?

        // argmax posterior
        unsigned int maxIndex = 0; // initialization value
        double max = -INFINITY;
        for (unsigned int k = 0; k < hmm->hiddenStates; k++) {
            if (posterior[k] > max) {
                maxIndex = k;
                max = posterior[k];
                //printf("max is %f\n", max);
            }
        }
        
    }
    
    free(scalingFactor);
    free(alpha);
    free(beta);
    
    return z;
}
