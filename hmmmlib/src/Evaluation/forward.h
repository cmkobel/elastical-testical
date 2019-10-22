#include <stdio.h>
#include "hmm.h"

#pragma once

/*
 
 Returns the likeliyhood for observing a sequence Y of length T
 given a HMM hmm
 
 */
double *forward(HMM *hmm, const unsigned int *Y, const unsigned int T, double * scalingFactor);
