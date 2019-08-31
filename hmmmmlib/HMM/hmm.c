#include "hmm.h"
#include <stdio.h>
#include <stdlib.h>

HMM * HMMCreate(const unsigned int hiddenStates, const unsigned int observations) {
    HMM * newHMM = malloc(sizeof(HMM));
    
    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;
    
    // The init probs
    newHMM->initProbs = malloc(sizeof(double)*hiddenStates);
    
    // The transition probability is a N*N matrix
    newHMM->transitionProbs = malloc(sizeof(double *)*hiddenStates);
    for(int i = 0; i < hiddenStates; i++){
        newHMM->transitionProbs[i] = malloc(sizeof(double)*hiddenStates);
    }
    
    // The emission probability is a M*N matrix
    newHMM->emissionProbs = malloc(sizeof(double *)*hiddenStates);
    for(int i = 0; i < hiddenStates; i++){
        newHMM->emissionProbs[i] = malloc(sizeof(double)*observations);
    }
    
    return newHMM;
}

bool valdidateHMM(const HMM *hmm){
    
    return true;
}


void printHMM(const HMM *hmm){
    printf("hello");
}
