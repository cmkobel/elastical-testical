#include "hmm.h"
#include <stdio.h>
#include <stdlib.h>

HMM * HMMCreate(const unsigned int hiddenStates, const unsigned int observations) {
    HMM * newHMM = calloc(1, sizeof(HMM));
    
    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;
    
    unsigned int i;
    
    // The init probs
    //
    // [state]
    //
    newHMM->initProbs = calloc(newHMM->hiddenStates ,sizeof(double));
    
    // The transition probability is a N*N matrix
    //
    // [from state][to state]
    //
    newHMM->transitionProbs = calloc(newHMM->hiddenStates, sizeof(double *));
    for(i = 0; i < hiddenStates; i++){
        newHMM->transitionProbs[i] = calloc(newHMM->hiddenStates, sizeof(double));
    }
    
    // The emission probability is a M*N matrix
    //
    // [state][observation]
    //
    newHMM->emissionProbs = calloc(newHMM->hiddenStates, sizeof(double *));
    for(int i = 0; i < newHMM->hiddenStates; i++){
        newHMM->emissionProbs[i] = calloc(newHMM->observations, sizeof(double));
    }
    
    return newHMM;
}

//should be static
bool valdidateHMM(const HMM *hmm){
    
    unsigned int i = 0;
    unsigned int j = 0;
    double sum = 0.0;
    
    //Summing initprobs
    for(i=0; i < hmm->hiddenStates; i++){
        sum += hmm->initProbs[i];
    }
    if(sum != 1.0){
        return false;
    }
    
    for (i = 0; i < hmm->hiddenStates; i++) {
        sum = 0.0;
        for (j = 0; j < hmm->hiddenStates; j++) {
            
        }
        if (sum != 1.0) {
            return false;
        }
    }
    
    return true;
}

//should be static
void printHMM(const HMM *hmm){
    
    unsigned int i;
    unsigned int j;
    
    //Printing init probs
    printf("Init probs\n");
    for(i=0; i < hmm->hiddenStates; i++){
        printf("%f, ", hmm->initProbs[i]);
    }
    
    printf("\n\n\n");
    
    //Print the transitionpos
    printf("Transition probs\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < hmm->hiddenStates; j++){
            printf("%f, ", hmm->transitionProbs[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\n\n");
    
    //Print the emissionprobs
    printf("Emission probs\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < hmm->observations; j++){
            printf("%f, ", hmm->emissionProbs[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\n\n");
}
