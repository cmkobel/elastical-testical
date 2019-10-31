#include "posteriorDecoding.h"
#include <stdlib.h>
#include <math.h>

double * posteriorDecoding(HMM * hmm, const int *Y, const int T){
    //                     hmm-obj    data          len(data)
    
    double * alpha = calloc(hmm->hiddenStates*T, sizeof(double));
    double * beta = calloc(hmm->hiddenStates*T, sizeof(double));
    double * scalingFactor = calloc(T, sizeof(double));
    forward(hmm, Y, T, scalingFactor, alpha); // scalingFactor bliver sat her.
    backward(hmm, Y, T, scalingFactor, beta); // scalingFactor bliver brugt her.

    //print alpha
    /* for (unsigned int i = 0; i < count; i++)
    {
        ;
    
    } */


    unsigned int * z = calloc(T, sizeof(unsigned int));
    double * z_ = calloc(T, sizeof(double));
    
    //double posterior; // Skal posterior ikke være en liste?
    double * posterior = calloc(hmm->hiddenStates, sizeof(double));

    for (unsigned int i = 0; i < T; i++) {
        for (unsigned int k = 0; k < hmm->hiddenStates; k++) {
            posterior[k] = alpha[i*T+k]*beta[i*T+k];
            /* if(alpha[i*T+k]*beta[i*T+k] > posterior){
                posterior = alpha[i*T+k]*beta[i*T+k];
            } */
        }

        // argmax posterior
        unsigned int maxIndex = 0; // initialization value
        double max = -INFINITY;
        for (unsigned int l = 0; l < hmm->hiddenStates; l++) {
            if (posterior[l] > max) {
                maxIndex = l;
                max = posterior[l];
                //printf("max is %f\n", max);
            }
        }
        z[i] = maxIndex;
        z_[i] = max;
        
    }
    
    free(scalingFactor);
    free(alpha);
    free(beta);
    
    
    for (unsigned int i = 0; i < T; i++) {
        printf("%d", z[i]);
    }
    printf("\n");
    
    printf("leaving\n");
    

    return z_;
}
