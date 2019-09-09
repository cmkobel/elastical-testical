#include <stdio.h>
#include <stdlib.h>


void viterbi(int n_obs, int n_states, double *start_p, double **trans_p, double** emit_p, int n_data, int *data, int* output);



int main() {
    // set hardcoded probs
    int n_states = 2; // healthy, fever
    int n_obs = 3; // normal, cold, dizzy

    double start_p_[2] = {0.6, 0.4};

    double trans_p_[2][2] = {{0.7, 0.3}, {0.4, 0.6}};
    double** trans_p = calloc(2, sizeof(double*));
    for (int i = 0; i < 2; i++) trans_p[i] = trans_p_[i]; // Hvornår allokerer vi kolonnerne?

    double emit_p_[2][3] = {{0.5, 0.4, 0.1}, {0.1, 0.3, 0.6}}; // [state][obs]
    double** emit_p = calloc(2, sizeof(double*));
    for (int i = 0; i < 2; i++) emit_p[i] = emit_p_[i];
    

    
    // feed data to the viterbi alg.
    int n_data = 7; 
    int data_[7] = {0, 1, 2, 2, 1, 1, 0}; // normal, cold, dizzy, dizzy, cold, cold, normal
    int* data = data_;
    
    int output_[7];





    viterbi(n_obs, n_states, (double*)&start_p_, trans_p, emit_p, n_data, data, (int*)&output_);

    printf("Viterbi decoding gives the following state sequence:\n");
    for (int i = 0; i < n_data; i++)
    {   
        printf("%i, ", output_[i]);
    }
    printf("\n");



    return 0;
}


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
