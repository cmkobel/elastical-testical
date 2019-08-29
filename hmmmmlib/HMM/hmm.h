#include <stdio.h>

typedef struct HMM HMM;
HMM * HMMCreate(int hiddenStates, int observations);

void HMMSetTransitionProbs(HMM * this, double ** transitionProbs);

