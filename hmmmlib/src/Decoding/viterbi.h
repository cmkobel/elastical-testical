#include "hmm.h"

unsigned int* viterbi(HMM *hmm, const int *Y, const int T);

unsigned int arrayMax(double* array, unsigned int length_of_array);
