#include <stdio.h>

#pragma once
#include "hmm.h"
//#include "forward.h"
#include "backward.h"

void baumWelch(HMM *hmm, const unsigned int *Y, const unsigned int T, const int itterations);
void assignRandomValues(HMM *hmm);
