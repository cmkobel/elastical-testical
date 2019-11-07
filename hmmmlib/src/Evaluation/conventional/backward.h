#include "hmm.h"
#pragma once

void backward(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor, double * beta);
