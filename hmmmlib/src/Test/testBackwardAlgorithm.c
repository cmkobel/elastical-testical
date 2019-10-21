#include "testBackwardAlgorithm.h"
#include "hmm.h"
#include "backward.h"
#include "forward.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

bool testBackwardAlgorithm() {
    HMM * hmm = HMMCreate(2, 2);
    
    double transitionProbs[2][2] = {
        {0.5, 0.5},
        {0.3, 0.7}
    };
    
    double emissionProbs[2][2] = {
        {0.3, 0.7},
        {0.8, 0.2}
    };
    
    double initProbs[2] = {0.2, 0.8};
    
    hmm->initProbs = initProbs;
    int i;
    int j;
    for(i = 0; i < hmm->hiddenStates; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            hmm->transitionProbs[i*hmm->hiddenStates+j] = transitionProbs[i][j];
        }
    }
    for(i = 0; i < hmm->hiddenStates; i++){
        for(j = 0; j < hmm->observations; j++){
            hmm->emissionProbs[i*hmm->observations+j] = emissionProbs[i][j];
        }
    }
    
    const unsigned int observation[10] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
    const unsigned int obsLenght = 10;
    
    double * scaleFactor = calloc(obsLenght, sizeof(double));
    double * alpha = forward(hmm, observation, obsLenght, scaleFactor);
    double * beta = backward(hmm, observation, obsLenght, scaleFactor);
    
    
    
    double test[20] = {1.000000, 1.000000,
        0.868282, 1.026152,
        0.862481, 1.041273,
        0.944879, 1.143683,
        1.449358, 1.754844,
        1.867152, 1.504211,
        1.267337, 0.950106,
        0.898670, 1.018426,
        0.853588, 1.025241,
        0.838962, 1.014856};
    
    
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < obsLenght; j++){
            assert(fabs(beta[i*obsLenght+j]-test[i*obsLenght+j]) < 0.00001);
        }
    }
    
    return true;
}
