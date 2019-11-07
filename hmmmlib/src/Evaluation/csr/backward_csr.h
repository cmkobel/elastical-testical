#include "hmm.h"
#pragma once
int b_csr(HMM * hmm, double ** sparseMatrixs, int * ia, int * ja, double * a);
void backward_csr(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * beta);
