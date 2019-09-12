//
//  TestsForwardAlgorithm.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 30/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include "TestsForwardAlgorithm.h"
#include "hmm.h"
#include "forward.h"
#include <assert.h>

bool testForwardAlgorithm() {
    HMM * hmm = HMMCreate(7, 4);
    
    double initProbs[7] = {0.0, 0.0, 0.2, 0.8, 0.0, 0.0, 0.0};
    
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
    
    
    for(i = 0; i < hmm->hiddenStates; i++){
        hmm->initProbs[i] = initProbs[i];
    }
    
    printHMM(hmm);

    int obsTest1[4] = {1, 1, 1, 2};
    int * obs = obsTest1;
    double * scalingFactor = calloc(4, sizeof(double));
    double ** forwardResult = forward(hmm, obs, 4, scalingFactor);
    
    //assert(forwardResult == 0.0067856249999999991);
    free(scalingFactor);
    scalingFactor = calloc(7, sizeof(double));
    int obsTest2[7] = {1, 1, 1, 2, 3, 3, 1};
    obs = obsTest2;
    forwardResult = forward(hmm, obs, 7, scalingFactor);
    
    printHMM(hmm);
    free(hmm);
    //assert(forwardResult == 0.00013674062499999999);
    
    return true;
}
