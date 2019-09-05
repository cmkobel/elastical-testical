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
#include <stdlib.h>
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
    
    for(i = 0; i < hmm->hiddenStates; i++){
        hmm->initProbs[i] = initProbs[i];
    }

    int obsTest1[4] = {1, 1, 1, 2};
    int * obs = obsTest1;
    double ** forwardResult = forward(hmm, obs, 4);
    
    //assert(forwardResult == 0.0067856249999999991);
    
    int obsTest2[7] = {1, 1, 1, 2, 3, 3, 1};
    obs = obsTest2;
    forwardResult = forward(hmm, obs, 7);

    //assert(forwardResult == 0.00013674062499999999);
    
    return true;
}
