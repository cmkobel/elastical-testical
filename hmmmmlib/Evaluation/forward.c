#include "forward.h"
#include <stdlib.h>

double ** forward(HMM *hmm, const int *Y, const int T, double * scalingFactor){
    
    
    
    unsigned int i;
    unsigned int j;
    
    // 2D alpha matrix
    //
    // [state][time]
    //
    double **alpha = calloc(hmm->hiddenStates, sizeof(double*));
    for(i = 0; i < hmm->hiddenStates; i++){
        alpha[i] = calloc(T, sizeof(double));
    }

    // Initial is the same as the initProbs times the probs of emitting Y[0]
    for(i = 0; i < hmm->hiddenStates; i++){
        alpha[i][0] = hmm->initProbs[i]*hmm->emissionProbs[i][Y[0]];
        scalingFactor[0] += alpha[i][0];
    }
    // Scaling step
    for(j = 0; j < hmm->hiddenStates; j++){
        alpha[j][0] = alpha[j][0]/scalingFactor[0];
    }
    
    // Now the "recursive" step starts
    for(i = 1; i < T; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            double emissionProb = hmm->emissionProbs[j][Y[i]];
            if(emissionProb > 0){
                double pastTransProb = 0.0;
                for(int l = 0; l < hmm->hiddenStates; l++){
                    pastTransProb += hmm->transitionProbs[l][j]*alpha[l][i-1];
                }
                alpha[j][i] = emissionProb*pastTransProb;
            }
            scalingFactor[i] += alpha[j][i];
        }
        // Scaling step
        for(j = 0; j < hmm->hiddenStates; j++){
            alpha[j][i] = alpha[j][i]/scalingFactor[i];
        }
    }
    
    printf("Forward\n");
    for(i = 0; i < T; i++){
        printf("%f, ", scalingFactor[i]);
    }
    printf("\n\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < T; j++){
            printf("%f, ", alpha[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    return alpha;
}
