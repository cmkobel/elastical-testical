#ifndef posteriorDecoding_h
#define posteriorDecoding_h

#pragma once

#include <stdio.h>
#include "forward.h"
#include "backward.h"
#include "hmm.h"

double * posteriorDecoding(HMM * hmm, const unsigned int *Y, const unsigned int T);

#endif
