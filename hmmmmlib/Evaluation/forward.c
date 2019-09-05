#include "forward.h"
#include <stdlib.h>

double ** forward(HMM *hmm, const int *Y, const int T){
    
    
    
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
    }
    
    // Now the "recursive" step starts
    for(i = 1; i < T; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            double emissionProb = hmm->emissionProbs[j][Y[i]];
            double pastTransProb = 0.0;
            for(int l = 0; l < hmm->hiddenStates; l++){
                pastTransProb += hmm->transitionProbs[j][l]*alpha[l][i-1];
            }
            alpha[j][i] = emissionProb*pastTransProb;
        }
    }
    /*
    printf("Forward\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < T; j++){
            printf("%f, ", alpha[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */
    return alpha;
}
