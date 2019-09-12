#include "TestBaumWelch.h"
#include "baumWelch.h"
#include "hmm.h"
#include <assert.h>

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
    
    const int observation[10] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0};
    const int obsLenght = 10;
    
    printf("BEFORE: \n");
    printHMM(hmm);
    baumWelch(hmm, observation, obsLenght, 1);
    
    // Checking the trans probs
    for(i = 0; i < hmm->hiddenStates*hmm->hiddenStates; i++){
        printf("%f, ", hmm->transitionProbs[i]);
    }
    assert(hmm->transitionProbs[0] == 0.43921478415604948);
    assert(hmm->transitionProbs[1*hmm->hiddenStates+1] == 0.78554317773503979);
    
    // Checking the emission probs
    assert(hmm->emissionProbs[0] == 0.46160107308583781);
    assert(hmm->emissionProbs[1*hmm->observations+1] == 0.084984433203479412);
    
    //printf("AFTER: \n");
    //printHMM(hmm);
    
    return valdidateHMM(hmm);
}
