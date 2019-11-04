//
//  TestsForwardAlgorithm.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 30/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include "TestsForwardAlgorithm.h"
#include "hmm.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

bool testForwardAlgorithm() {
    HMM * hmmCon = HMMConventional(2, 2);
    HMM * hmmBLAS = HMMBLAS(2, 2);
    
    double transitionProbs[2][2] = {
        {0.5, 0.5},
        {0.3, 0.7}
    };
    
    double emissionProbs[2][2] = {
        {0.3, 0.7},
        {0.8, 0.2}
    };
    
    double initProbs[2] = {0.2, 0.8};
    
    for(unsigned int i = 0; i < hmmCon->hiddenStates; i++){
        hmmCon->initProbs[i] = initProbs[i];
        hmmBLAS->initProbs[i] = initProbs[i];
    }

    
    int i;
    int j;
    for(i = 0; i < hmmCon->hiddenStates; i++){
        for(j = 0; j < hmmCon->hiddenStates; j++){
            hmmBLAS->transitionProbs[i*hmmCon->hiddenStates+j] = transitionProbs[i][j];
            hmmCon->transitionProbs[i*hmmCon->hiddenStates+j] = transitionProbs[i][j];
        }
    }
    for(i = 0; i < hmmCon->hiddenStates; i++){
        for(j = 0; j < hmmCon->observations; j++){
            hmmBLAS->emissionProbs[i*hmmCon->observations+j] = emissionProbs[i][j];
            hmmCon->emissionProbs[i*hmmCon->observations+j] = emissionProbs[i][j];
        }
    }
    
    const unsigned int observation[10] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
    const unsigned int obsLenght = 10;
    
    double * alphaCon = calloc(hmmCon->hiddenStates*obsLenght, sizeof(double));
    double * alphaBLAS = calloc(hmmCon->hiddenStates*obsLenght, sizeof(double));
    
    double * scaleFactorAlpha = calloc(obsLenght, sizeof(double));
    double * scaleFactorBLAS = calloc(obsLenght, sizeof(double));
    
    F(hmmCon, observation, obsLenght, scaleFactorAlpha, alphaCon);
    F(hmmBLAS, observation, obsLenght, scaleFactorBLAS, alphaBLAS);
    
    double test[20] = {
        0.085714, 0.914286,
        0.148330, 0.851670,
        0.155707, 0.844293,
        0.156585, 0.843415,
        0.156690, 0.843310,
        0.634280, 0.365720,
        0.722736, 0.277264,
        0.230843, 0.769157,
        0.165653, 0.834347,
        0.157773, 0.842227
    };
    
    
    for(i = 0; i < obsLenght; i++){
        for(j = 0; j < hmmCon->hiddenStates; j++){
            assert(abs(alphaBLAS[i*hmmCon->hiddenStates+j]-test[i*hmmCon->hiddenStates+j] < 0.00001));
            assert(abs(alphaCon[i*hmmCon->hiddenStates+j]-test[i*hmmCon->hiddenStates+j] < 0.00001));
        }
    }
    
    
    HMMDeallocate(hmmCon);
    HMMDeallocate(hmmBLAS);
    
    return true;
}
