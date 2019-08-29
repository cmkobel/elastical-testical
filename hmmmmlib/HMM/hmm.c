#include "hmm.h"
#include <stdio.h>
#include <stdlib.h>

struct HMM {
    
    int hiddenStates;
    int observations;
    double ** transitionProbs;
    double ** emissionProbs;
    
};

HMM * HMMCreate(int hiddenStates, int observations) {
    HMM * newHMM = malloc(sizeof(HMM));
    
    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;
    
    // The transition probability is a N*N matrix
    newHMM->transitionProbs = malloc(sizeof(double *)*hiddenStates);
    for(int i = 0; i < hiddenStates; i++){
        newHMM->transitionProbs[i] = malloc(sizeof(double)*hiddenStates);
    }
    
    // The emission probability is a N*M matrix
    newHMM->emissionProbs = malloc(sizeof(double *)*observations);
    for(int i = 0; i < observations; i++){
        newHMM->emissionProbs[i] = malloc(sizeof(double)*hiddenStates);
    }
    
    return newHMM;
}

void HMMSetTransitionProbs(HMM * this, double ** transitionProbs){
    
    
    
}
