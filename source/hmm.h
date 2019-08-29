typedef struct HMM HMM;
HMM * HMMCreate(int hiddenStates, int observations, float transitionProbs);

void HMMSetTransitionProbs(HMM * this, int transitionProbs);

