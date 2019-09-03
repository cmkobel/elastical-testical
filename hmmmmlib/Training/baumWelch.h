#include <stdio.h>

#include "hmm.h"
#include "forward.h"
#include "backward.h"

void baumWelch(HMM *hmm, const int *Y, const int T);
void assignRandomValues(HMM *hmm);
