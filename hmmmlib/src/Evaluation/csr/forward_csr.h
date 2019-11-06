#include "hmm.h"
#pragma once

void forward_csr(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * alpha);
