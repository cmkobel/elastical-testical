#include "hmm.h"
#include <stdio.h>
#include <stdlib.h>

HMM * HMMCreate(const unsigned int hiddenStates, const unsigned int observations) {
    HMM * newHMM = malloc(sizeof(HMM));
    
    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;
    
    unsigned int i;
    unsigned int j;
    
    // The init probs
    newHMM->initProbs = malloc(sizeof(double)*hiddenStates);
    for(i=0; i< newHMM->hiddenStates; i++){
        newHMM->initProbs[i] = 0.0;
    }
    
    // The transition probability is a N*N matrix
    newHMM->transitionProbs = malloc(sizeof(double *)*hiddenStates);
    for(i = 0; i < hiddenStates; i++){
        newHMM->transitionProbs[i] = malloc(sizeof(double)*hiddenStates);
    }
    for(i=0; i< newHMM->hiddenStates; i++){
        for(j=0; j < newHMM->hiddenStates; j++){
            newHMM->transitionProbs[i][j] = 0.0;
        }
    }
    
    // The emission probability is a M*N matrix
    newHMM->emissionProbs = malloc(sizeof(double *)*hiddenStates);
    for(int i = 0; i < hiddenStates; i++){
        newHMM->emissionProbs[i] = malloc(sizeof(double)*observations);
    }
    for(i=0; i< newHMM->hiddenStates; i++){
        for(j=0; j < newHMM->observations; j++){
            newHMM->emissionProbs[i][j] = 0.0;
        }
    }
    
    return newHMM;
}

//should be static
bool valdidateHMM(const HMM *hmm){
    
    return true;
}

//should be static
void printHMM(const HMM *hmm){
    
    unsigned int i;
    unsigned int j;
    
    //Printing init probs
    for(i=0; i < hmm->hiddenStates; i++){
        printf("%f, ", hmm->initProbs[i]);
    }
    
    printf("\n\n\n");
    
    //Print the transitionpos
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < hmm->hiddenStates; j++){
            printf("%f, ", hmm->transitionProbs[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\n\n");
    
    //Print the emissionprobs
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < hmm->observations; j++){
            printf("%f, ", hmm->emissionProbs[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\n\n");
}
