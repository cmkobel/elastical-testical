typedef struct HMM HMM;
HMM * HMMCreate(int hiddenStates, int observations);

void HMMSetStates(HMM * this, int hiddenStates);
void HMMSetObservation(HMM * this, int observations);


