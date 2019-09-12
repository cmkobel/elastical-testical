#include <stdio.h>
#include <stdbool.h>
#pragma once

struct HMM {
    
    unsigned int hiddenStates;
    unsigned int observations;
    double ** transitionProbs;
    double ** emissionProbs;
    double * initProbs;
    
};
typedef struct HMM HMM;

HMM * HMMCreate(const unsigned int hiddenStates, const unsigned int observations);

bool valdidateHMM(const HMM *hmm);

void printHMM(const HMM *hmm);
