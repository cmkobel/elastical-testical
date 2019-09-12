#include "hmm.h"

void viterbi(int n_obs, int n_states, double *start_p, double **trans_p, double** emit_p, int n_data, int *data, int* output);
