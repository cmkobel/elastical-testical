#include <stdio.h>
#include <stdbool.h>

struct HMM {
    
    int hiddenStates;
    int observations;
    double ** transitionProbs;
    double ** emissionProbs;
    double * initProbs;
    
};
typedef struct HMM HMM;

HMM * HMMCreate(const unsigned int hiddenStates, const unsigned int observations);

bool ValdidateHMM(HMM *hmm);
