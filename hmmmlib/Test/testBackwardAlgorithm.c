#include "testBackwardAlgorithm.h"
#include "hmm.h"

#include <assert.h>
#include <stdlib.h>
#include <math.h>

extern bool testBackwardAlgorithm() {
    HMM * hmmCon = HMMConventional(2, 2);
    
    double transitionProbs[2][2] = {
        {0.5, 0.5},
        {0.3, 0.7}
    };
    
    double emissionProbs[2][2] = {
        {0.3, 0.7},
        {0.8, 0.2}
    };
    
    double initProbs[2] = {0.2, 0.8};
    
    hmmCon->initProbs = initProbs;
    int i;
    int j;
    for(i = 0; i < hmmCon->hiddenStates; i++){
        for(j = 0; j < hmmCon->hiddenStates; j++){
            hmmCon->transitionProbs[i*hmmCon->hiddenStates+j] = transitionProbs[i][j];
        }
    }
    for(i = 0; i < hmmCon->hiddenStates; i++){
        for(j = 0; j < hmmCon->observations; j++){
            hmmCon->emissionProbs[i*hmmCon->observations+j] = emissionProbs[i][j];
        }
    }
    
    const unsigned int observation[10] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
    const unsigned int obsLenght = 10;
    double * alphaCon = calloc(hmmCon->hiddenStates*obsLenght, sizeof(double));
    double * betaCon = calloc(hmmCon->hiddenStates*obsLenght, sizeof(double));
    
    double * scaleFactor = calloc(obsLenght, sizeof(double));
    F(hmmCon, observation, obsLenght, scaleFactor, alphaCon);
    B(hmmCon, observation, obsLenght, scaleFactor, betaCon);
    
    double test[20] = {
        0.838486, 1.015142,
        0.848495, 1.026387,
        0.854859, 1.026767,
        0.898964, 1.018758,
        1.267584, 0.950282,
        1.076550, 0.867237,
        0.944879, 1.143683,
        0.862481, 1.041273,
        0.868282, 1.026152,
        1.000000, 1.000000
    };
    
    
    for(i = 0; i < obsLenght; i++){
       for(j = 0; j < hmmCon->hiddenStates; j++){
           assert(abs(betaCon[i*hmmCon->hiddenStates+j] - test[i*hmmCon->hiddenStates+j] < 0.00001));
       }
    }
    
    return true;
}
