#include "hmm.h"

int* viterbi(HMM *hmm, const int *Y, const int T);

unsigned int argMax(double* array_, unsigned int length);
