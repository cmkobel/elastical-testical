#include <stdio.h>
#include <stdbool.h>
#pragma once

struct HMM {
    
    unsigned int hiddenStates;
    unsigned int observations;
    double * transitionProbs;
    double * emissionProbs;
    double * initProbs;
    
    const struct vFuncs * funcs;
    
};

typedef struct HMM HMM;

struct vFuncs{
    
    void *(*forward)(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * alpha);
    void *(*backward)(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * beta);
    
};

HMM * HMMCreate(const unsigned int hiddenStates, const unsigned int observations, const struct vFuncs * funcs);

bool valdidateHMM(const HMM *hmm);

void F(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * alpha);

void B(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * beta);

void printHMM(const HMM *hmm);

void HMMDeallocate(HMM * hmm);

extern const struct vFuncs conventional[];
