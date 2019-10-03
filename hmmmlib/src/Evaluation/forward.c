#include "forward.h"
#include <stdlib.h>

double * forward(HMM *hmm, const int *Y, const int T, double * scalingFactor){
    
    unsigned int i;
    unsigned int j;
    

    // 2D alpha matrix
    //
    // [state][time]
    //
    double * alpha = calloc(hmm->hiddenStates*T, sizeof(double));

    // Initial is the same as the initProbs times the probs of emitting Y[0]
    for(i = 0; i < hmm->hiddenStates; i++){
        alpha[i*T+0] = hmm->initProbs[i]*hmm->emissionProbs[i*hmm->observations+Y[0]];
        scalingFactor[0] += alpha[i*T+0];
    }
    // Scaling step
    for(j = 0; j < hmm->hiddenStates; j++){
        alpha[j*T+0] = alpha[j*T+0]/scalingFactor[0];
    }
    
    // Now the "recursive" step starts
    for(i = 1; i < T; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            double emissionProb = hmm->emissionProbs[j*hmm->observations+Y[i]];
            if(emissionProb > 0){
                double pastTransProb = 0.0;
                for(int l = 0; l < hmm->hiddenStates; l++){
                    pastTransProb += hmm->transitionProbs[l*hmm->hiddenStates+j]*alpha[l*T+i-1];
                }
                alpha[j*T+i] = emissionProb*pastTransProb;
            }
            scalingFactor[i] += alpha[j*T+i];
        }
        // Scaling step
        for(j = 0; j < hmm->hiddenStates; j++){
            alpha[j*T+i] = alpha[j*T+i]/scalingFactor[i];
        }
    }
    /*
    printf("\n\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < T; j++){
            printf("%f, ", alpha[i*T+j]);
        }
        printf("\n");
    }
    printf("\n");
    */
    return alpha;
}
