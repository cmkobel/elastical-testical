#ifndef posteriorDecoding_h
#define posteriorDecoding_h

#pragma once

#include <stdio.h>
#include "forward_blas.h"
#include "backward_blas.h"
#include "hmm.h"

double * posteriorDecoding(HMM * hmm, const unsigned int *Y, const unsigned int T);

#endif
