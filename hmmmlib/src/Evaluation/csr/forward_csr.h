#include "hmm.h"
#pragma once
int csr(HMM * hmm, double ** sparseMatrixs, int * ia, int * ja, double * a);
void forward_csr(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * alpha);
