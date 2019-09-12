#include "hmm.h"

double** viterbi(HMM *hmm, int n_obs, int n_states, double *start_p, double **trans_p, double** emit_p, int n_data, int *data, int* output);
