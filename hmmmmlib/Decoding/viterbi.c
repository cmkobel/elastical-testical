#include <stdio.h>
#include <stdlib.h>
#include "viterbi.h"

void viterbi(int n_states, int n_obs, double *start_p, double **trans_p, double **emit_p, int n_data, int *data, int* output) {

    // TODO save output


    double* probs = calloc(n_states, sizeof(double)); 
    double max_ = 0.0;

    int hidden_state = -1; // -1 for uninitialized value


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
    printf("hs is %i with p = %f\n\n", hidden_state, max_);


    // Second observation onwards.
    for (int i = 1; i < n_data; ++i) {
        
        // Debug
        printf("i = %d\n", i);
        
        
        // For each state
        for (int j = 0; j < n_states-1; j++) {
            
            // Calculate prob. based on data.
            probs[j] = max_ * trans_p[hidden_state][j] * emit_p[j][data[i]];
            printf("P_state_%d = %f\n", j, probs[j]);
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
        printf("hs is %i with p = %f\n\n", hidden_state, max_);

    }

}
