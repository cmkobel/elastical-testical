//
//  ForwardAlgorithmTest.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 30/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include <stdio.h>
#import "hmm.h"

int testForwardAlgorithm() {
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
    
    
    for(int i = 0; i < 7; i++){
        printf("%f", emissionProbs[i][0]);
    }
    
    
    printf("hello world");
    
    return 0;
}
