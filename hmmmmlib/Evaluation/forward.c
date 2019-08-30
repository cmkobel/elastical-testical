#include "forward.h"
#include <stdlib.h>

double forward(HMM *hmm, const int *Y, const int T){
    
    unsigned int i = 0;
    
    double **alpha = malloc(sizeof(double*)*hmm->hiddenStates);
    for(i = 0; i < hmm->hiddenStates; i++){
        alpha[i] = malloc(sizeof(double)*T);
    }
    
    // Initial is the same as the initProbs times the probs of emitting Y[0]
    for(i = 0; i < hmm->hiddenStates; i++){
        alpha[i][0] = hmm->initProbs[i]*hmm->emissionProbs[Y[0]][i];
    }
    
    // Now the "recursive" step starts
    for(i = 1; i < T; i++){
        for(int j = 0; j < hmm->hiddenStates; j++){
            double emissionProb = hmm->emissionProbs[Y[i]][j];
            double pastTransProb = 0.0;
            for(int l = 0; l < hmm->hiddenStates; l++){
                pastTransProb += hmm->transitionProbs[i-1][l]*alpha[i-1][l];
            }
            alpha[i][j] = emissionProb*pastTransProb;
        }
    }
    // Summing over the last column in alpha
    double probOfObservingY = 0;
    for(i = 0; i < hmm->hiddenStates; i++){
        probOfObservingY += alpha[T][i];
    }
    
    return probOfObservingY;
}
