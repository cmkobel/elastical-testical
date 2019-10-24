//
//  TestsForwardAlgorithm.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 30/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include "TestsForwardAlgorithm.h"
#include "hmm.h"
#include "forward_blas.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

bool testForwardAlgorithm() {
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
    double * alpha = calloc(hmm->hiddenStates*obsLenght, sizeof(double));
    forward(hmm, observation, obsLenght, scaleFactor, alpha);
    
    double test[20] = {0.085714, 0.914286,
        0.148330, 0.851670,
        0.155707, 0.844293,
        0.156585, 0.843415,
        0.156690, 0.843310,
        0.634280, 0.365720,
        0.722736, 0.277264,
        0.230843, 0.769157,
        0.165653, 0.834347,
        0.157773, 0.842227};
    
    for (j = 0; j < obsLenght; j++){
        for(i = 0; i < hmm->hiddenStates; i++) {
            assert(fabs(alpha[j*hmm->hiddenStates+i]-test[j*hmm->hiddenStates+i]) < 0.00001);
        }
    }
    
    return true;
}
