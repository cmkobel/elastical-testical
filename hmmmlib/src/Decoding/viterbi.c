#include <stdio.h>
#include <stdlib.h>
#include "viterbi.h"

int* viterbi(HMM *hmm, int n_states, int n_obs, double *start_p, double **trans_p, double **emit_p, int n_data, int *data) {
    
    
    /*
    double** outputTable = calloc(hmm->hiddenStates, sizeof(double*));
    for (int i = 0; i < hmm->hiddenStates; ++i) {
        outputTable[i] = calloc(n_data, sizeof(double));
    }
    */
    int* output = calloc(n_data, sizeof(int));


    double* probs = calloc(n_states, sizeof(double)); 
    double max_ = 0.0;

    int hidden_state = -1; // -1 for uninitialized value


    // i = 0:
    // First observation, based on start_p rather than trans_p.
    for (int j = 0; j < n_states-1; j++) {

        // Calculate probability based on data
        probs[j] = start_p[j]*emit_p[j][data[0]];

        
        printf("P_state_%d = %f\n", j, probs[j]);
        
        // Find the state with the highest prob.
        if (probs[j] > max_) {
            max_ = probs[j];
            hidden_state = j; 
        }
    }
    output[0] = hidden_state;

    // Debug
    // printf("hs is %i with p = %f\n\n", hidden_state, max_);
    printf("0: hs is %i with p = %f\n", hidden_state, max_);


    // i >= 1:
    // Second observation onwards.
    for (int i = 1; i < n_data; ++i) {
        
        // Debug
        // printf("i = %d\n", i);
        
        
        // For each state
        for (int j = 0; j < n_states-1; j++) {
            
            // Calculate prob. based on data.
            probs[j] = max_ * trans_p[hidden_state][j] * emit_p[j][data[i]];

            //outputTable[j][i] = max_ * trans_p[hidden_state][j] * emit_p[j][data[i]];
        }


        // Find the hidden state and its prob.
        max_ = 0.0;
        for (int j = 0; j < n_states-1; j++) {
            if (probs[j] > max_) {
                max_ = probs[j];
                hidden_state = j;
            }
        }
        output[i] = hidden_state;
        printf("%i: hs is %i with p = %f\n", i, hidden_state, max_);

    }
    return output;

}
