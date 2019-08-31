//
//  TestsForwardAlgorithm.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 30/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include "TestsForwardAlgorithm.h"
#import "hmm.h"
#import "forward.h"

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
    
    
    //Print the transitionpos
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < hmm->hiddenStates; j++){
            printf("%f, ", hmm->transitionProbs[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\n\n");
    
    //Print the emissionprobs
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < hmm->observations; j++){
            printf("%f, ", hmm->emissionProbs[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\n\n");
    
    //Printing init probs
    for(i=0; i < hmm->hiddenStates; i++){
        printf("%f, ", hmm->initProbs[i]);
    }
    
    printf("\n\n\n");
    
    int observations[4] = {0, 1, 1, 2};
    int * obs = observations;
    double forwardResult = forward(hmm, obs, 4);
    
    printf("Forward Algorithm: %f", forwardResult);
    
    printf("\n\n\n");
    
    printHMM(hmm);
    
    return true;
}
