#include <stdio.h>

struct HMM {
    
    int hiddenStates;
    int observations;
    double ** transitionProbs;
    double ** emissionProbs;
    
};
typedef struct HMM HMM;

HMM * HMMCreate(int hiddenStates, int observations);
