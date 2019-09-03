#include "forward.h"
#include <stdlib.h>

double ** forward(HMM *hmm, const int *Y, const int T){
    
    
    
    unsigned int i;
    unsigned int j;
    
    double **alpha = calloc(hmm->hiddenStates, sizeof(double*));
    for(i = 0; i < hmm->hiddenStates; i++){
        alpha[i] = calloc(T, sizeof(double));
    }
    
    /*
    printf("\n Printing Y\n");
    for(i=0; i < T; i++) printf("%d, ", Y[i]);
    
    printf("\n Printing after callocing memory\n");
    
    for(i = 0; i < hmm->hiddenStates; i++){
        for(j = 0; j < T; j++){
            printf("%f, ", alpha[i][j]);
        }
        printf("\n");
    }
    
    printf("End printing \n");
    */
     
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
                pastTransProb += hmm->transitionProbs[i-1][l]*alpha[l][i-1];
            }
            alpha[j][i] = emissionProb*pastTransProb;
        }
    }
    
    /*
    for(i = 0; i < hmm->hiddenStates; i++){
        for(j = 0; j < T; j++){
            printf("%f, ", alpha[i][j]);
        }
        printf("\n");
    }
    */
    /*
    // Summing over the last column in alpha
    double probOfObservingY = 0;
    for(i = 0; i < hmm->hiddenStates; i++){
        probOfObservingY += alpha[i][T-1];
    }
    
    //printf("%f \n", probOfObservingY);

    for(i = 0; i < hmm->hiddenStates; i++){
        free(alpha[i]);
    }
    free(alpha);
    */
    
    return alpha;
}
