#include "hmm.h"
#pragma once

double *backward(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor);
