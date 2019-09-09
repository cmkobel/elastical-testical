#include <stdio.h>

#pragma once
#include "hmm.h"
#include "forward.h"
#include "backward.h"

void baumWelch(HMM *hmm, const int *Y, const int T, const int itterations);
void assignRandomValues(HMM *hmm);
