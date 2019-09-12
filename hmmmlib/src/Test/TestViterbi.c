#include "TestViterbi.h"
#include "viterbi.h"
#include "hmm.h"


#include <stdlib.h>
#include <assert.h>



bool testViterbi() {
    HMM * hmm = HMMCreate(7, 4);
    
    //double initProbs[7] = {0.0, 0.0, 0.2, 0.8, 0.0, 0.0, 0.0};
    double initProbs[7] = {0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00};
    
    
    double transitionProbs[7][7] ={
        {0.00, 0.00, 0.90, 0.10, 0.00, 0.00, 0.00},
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.05, 0.90, 0.05, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00},
        {0.00, 0.00, 0.00, 0.10, 0.90, 0.00, 0.00},
    };
    
    double emissionProbs[7][4] = {
        {0.30, 0.25, 0.25, 0.20},
        {0.20, 0.35, 0.15, 0.30},
        {0.40, 0.15, 0.20, 0.25},
        {0.25, 0.25, 0.25, 0.25},
        {0.20, 0.40, 0.30, 0.10},
        {0.30, 0.20, 0.30, 0.20},
        {0.15, 0.30, 0.20, 0.35}
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
    
    int obsTest1[8] = {0, 1, 2, 3, 3, 2, 1, 0}; // A C G T T G C A
    int * obs = obsTest1;
    int nData = 8;
    int * viterbiResult = viterbi(hmm, obs, nData);
    assert(viterbiResult[0] == 32837);
    
    
    
    return true;
}
