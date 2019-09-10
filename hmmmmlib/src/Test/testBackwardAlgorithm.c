#include "testBackwardAlgorithm.h"
#include "hmm.h"
#include "backward.h"
#include <assert.h>

bool testBackwardAlgorithm() {
    HMM * hmm = HMMCreate(7, 4);
    
    double transitionProbs[7][7] = {
        {0.0,0.0,0.9,0.1,0.0,0.0,0.0},
        {1.0,0.0,0.0,0.0,0.0,0.0,0.0},
        {0.0,1.0,0.0,0.0,0.0,0.0,0.0},
        {0.0,0.0,0.05,0.9,0.05,0.0,0.0},
        {0.0,0.0,0.0,0.0,0.0,1.0,0.0},
        {0.0,0.0,0.0,0.0,0.0,0.0,1.0},
        {0.0,0.0,0.0,0.1,0.9,0.0,0.0},
    };
    
    double emissionProbs[7][4] = {
        {0.3,0.25,0.25,0.2},
        {0.2,0.35,0.15,0.3},
        {0.4,0.15,0.2,0.25},
        {0.25,0.25,0.25,0.25},
        {0.2,0.4,0.3,0.1},
        {0.3,0.2,0.3,0.2},
        {0.15,0.3,0.2,0.35}
    };
    
    
    unsigned int i;
    unsigned int j;
    
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            hmm->transitionProbs[i][j] = transitionProbs[i][j];
        }
    }
    
    for(i = 0; i < 7; i++){
        for(j = 0; j < 4; j++){
            hmm->emissionProbs[i][j] = emissionProbs[i][j];
        }
    }
    
    int obsTest1[4] = {1, 1, 1, 2};
    int *obs = obsTest1;
    double * scalingFactor = calloc(4, sizeof(double));
    double **backWardResult = backward(hmm, obs, 4, scalingFactor);
    
    return true;
}
