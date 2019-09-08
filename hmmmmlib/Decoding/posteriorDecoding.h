#ifndef posteriorDecoding_h
#define posteriorDecoding_h

#include <stdio.h>
#include "forward.h"
#include "backward.h"
#include "hmm.h"

int posteriorDecoding(HMM * hmm, const int *Y, const int T, const int t);

#endif
