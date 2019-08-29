#include "hmm.h"
#include <stdio.h>
#include <stdlib.h>

struct HMM {
    int hiddenStates;
    int observations;
    float transitionProbs;

};

HMM * HMMCreate(int hiddenStates, int observations, float transitionProbs) {
    HMM * newHMM = malloc(sizeof(HMM));
    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;
    newHMM->transitionProbs = transitionProbs;

}