#include "hmm.h"

struct HMM {
    int hiddenStates;
    int observations;
};

HMM * HMMCreate(int hiddenStates, int observations){
    HMM * newHMM = malloc(sizeof(HMM));
    newHMM->hiddenStates = hiddenStates;
    newHMM->observations = observations;
}