#include "testBackwardAlgorithm.h"
#include "hmm.h"
#include "backward.h"
#include "forward.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

bool testBackwardAlgorithm() {
    
    /*
     
     TEST 1 - 2*2 HMM
     
     */
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
        1.076550, 0.867237,
        1.267584, 0.950282,
        0.898964, 1.018758,
        0.854859, 1.026767,
        0.848495, 1.026387,
        0.838486, 1.015142};
    
    
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < obsLenght; j++){
            assert(fabs(beta[i*obsLenght+j]-test[i*obsLenght+j]) < 0.00001);
        }
    }
    
    /*
     
     TEST 2 - 7*7 hmm
     
     */
    
    return true;
}
