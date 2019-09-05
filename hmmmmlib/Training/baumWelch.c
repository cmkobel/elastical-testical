#include "baumWelch.h"
#include <stdlib.h>

HMM * baumWelch(HMM *hmm, const int *Y, const int T){
    
    //Initial random init of HMM
    
    unsigned int i;
    unsigned int j;
    unsigned int l;
    
    // Gamma 2d matrix
    //
    // [time][state]
    //
    double ** gamma = calloc(T, sizeof(double*));
    for(i = 0; i < T; i++){
        gamma[i] = calloc(hmm->hiddenStates, sizeof(double));
    }
    
    // Xi 3d matrix
    //
    // [state][state][time]
    //
    double *** xi = (double ***)calloc(hmm->hiddenStates, sizeof(double**));
    for(i = 0; i < hmm->hiddenStates; i++){
        xi[i] = (double **)calloc(hmm->hiddenStates, sizeof(double*));
        for(j = 0; j < hmm->hiddenStates; j++){
            xi[i][j] = (double *)calloc(T, sizeof(double));
        }
    }

    for(int q = 0; q < 1; q++) {
        
        double ** alpha = forward(hmm, Y, T);
        double ** beta = backward(hmm, Y, T);
        
        // Updating gamma
        for(i = 0; i < T; i++){
            for (j = 0; j < hmm->hiddenStates; j++) {
                double numerator = alpha[j][i]*beta[j][i];
                double denominator = 0.0;
                for(l = 0; l < hmm->hiddenStates; l++){
                    denominator += alpha[l][i]*beta[l][i];
                }
                gamma[i][j] = numerator/denominator;
            }
        }
        
        printf("Gamma\n");
        for(i = 0; i < T; i++) {
            for (j = 0; j < hmm->hiddenStates; j++){
                printf("%f, ", gamma[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        
        // xi denominator
        double * xiDenominator = calloc(T, sizeof(double));
        
        for(l = 0; l < T; l++){
            for(i = 0; i < hmm->hiddenStates; i++){
                for(j = 0; j < hmm->hiddenStates; j++){
                    xiDenominator[l] += alpha[i][l]*beta[i][l+1]*hmm->transitionProbs[i][j]*hmm->emissionProbs[j][Y[l+1]];
                }
            }
        }
        
        // Updating xi
        for(i = 0; i < hmm->hiddenStates; i++){
            for(j = 0; j < hmm->hiddenStates; j++){
                for(l = 0; l < T; l++){
                    double numerator = alpha[i][l]*beta[i][l+1]*hmm->transitionProbs[i][j]*hmm->emissionProbs[j][Y[i+1]];
                    double denominator = xiDenominator[l];
                    xi[i][j][l] = numerator/denominator;
                }
            }
        }
        
        //Updating initial probs
        for (i = 0; i < hmm->hiddenStates; i++) {
            hmm->initProbs[i] = gamma[0][i];
        }
        
        //Updating transition probs
        for (i = 0; i < hmm->hiddenStates; i++) {
            for (j = 0; j < hmm->hiddenStates; j++) {
                double xiSum = 0.0;
                double gammaSum = 0.0;
                for(l = 0; l < T; l++){
                    xiSum += xi[i][j][l];
                    gammaSum += gamma[i][l];
                }
                hmm->transitionProbs[i][j] = xiSum/gammaSum;
            }
        }
        
        //Updating observations probs
        for (i = 0; i < hmm->hiddenStates; i++) {
            for (j = 0; j < hmm->observations; j++) {
                double numerator = 0.0;
                double denominator = 0.0;
                for(l = 0; l < T; l++){
                    if(Y[l] == j){
                        numerator += gamma[i][l];
                    }
                    denominator += gamma[i][l];
                }
                hmm->emissionProbs[i][j] = numerator/denominator;
            }
        }
    }
    
    free(gamma);
    
    return hmm;
}

// Asign random variables to all initprobs, transprobs and obsprobs
void assignRandomValues(HMM *hmm){
    
    
    
}
