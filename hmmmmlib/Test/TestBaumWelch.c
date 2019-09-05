#include "TestBaumWelch.h"
#include "baumWelch.h"
#include "hmm.h"

bool testBaumWelch() {
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
    for(int i = 0; i < 2; i++) hmm->transitionProbs[i] = transitionProbs[i];
    for(int i = 0; i < 2; i++) hmm->emissionProbs[i] = emissionProbs[i];
    
    const int observation[10] = {0, 0, 0, 0, 0, 1, 1, 0, 0};
    const int obsLenght = 10;
    
    printHMM(hmm);
    
    hmm = baumWelch(hmm, observation, obsLenght);
    
    printHMM(hmm);
    
    return true;
}
