#include "testBackwardAlgorithm.h"
#include "hmm.h"
#include "backward.h"
//#include "backward.c"


#include "forward.h"
//#include "forward.c"

#include <assert.h>
#include <stdlib.h>
#include <math.h>

extern bool testBackwardAlgorithm() {
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
    double * alpha = calloc(hmm->hiddenStates*obsLenght, sizeof(double));
    double * beta = calloc(hmm->hiddenStates*obsLenght, sizeof(double));
    
    double * scaleFactor = calloc(obsLenght, sizeof(double));
    forward(hmm, observation, obsLenght, scaleFactor, alpha);
    backward(hmm, observation, obsLenght, scaleFactor, beta);
    
    /* 
    printf("scaleFactor from backward");
    for (unsigned int i = 0; i < obsLenght; i++) {
        
        printf(" %f", scaleFactor[i]);
    }
    printf("\n");
     */
    
    double test[20] = {0.838486, 0.848495, 0.854859, 0.898964, 1.267584, 1.076550, 0.944879, 0.862481, 0.868282, 1.000000, 1.015142, 1.026387, 1.026767, 1.018758, 0.950282, 0.867237, 1.143683, 1.041273, 1.026152, 1.000000};
    
    
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < obsLenght; j++){
            assert(fabs(beta[i*obsLenght+j]-test[i*obsLenght+j]) < 0.00001);
        }
    }
    
    return true;
}
