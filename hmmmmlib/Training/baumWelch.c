#include "baumWelch.h"
#include <stdlib.h>

void baumWelch(HMM *hmm, const int *Y, const int T){
    
    //Initial random init of HMM
    assignRandomValues(hmm);
    
    bool converge = false;
    
    unsigned int i;
    unsigned int j;
    
    double ** gamma = calloc(T, sizeof(double*));
    for(i = 0; i < T; i++){
        gamma[i] = calloc(hmm->hiddenStates, sizeof(double));
    }
    
    double *** xi = (double ***)calloc(hmm->hiddenStates, sizeof(double**));
    for(i = 0; i < hmm->hiddenStates; i++){
        xi[i] = (double **)calloc(hmm->hiddenStates, sizeof(double*));
        for(j = 0; j < hmm->hiddenStates; j++){
            xi[i][j] = (double *)calloc(T, sizeof(double));
        }
    }

    while (converge) {
        
        double ** alpha = forward(hmm, Y, T);
        double ** beta = backward(hmm, Y, T);
        
        // Updating gamma
        for(i = 0; i < T; i++){
            for (j = 0; j < hmm->hiddenStates; j++) {
                
                
            }
        }
        
        // Updating xi
        for(i = 0; i < T; i++){
            for (j = 0; j < hmm->hiddenStates; j++) {
                
                
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
                
                
                
                
            }
        }
        
        //Updating observations probs
        for (i = 0; i < hmm->observations; i++) {
            for (j = 0; j < hmm->hiddenStates; j++) {
                
                
                
                
            }
        }
    
    }
    
    
}

// Asign random variables to all initprobs, transprobs and obsprobs
void assignRandomValues(HMM *hmm){
    
    
    
}
