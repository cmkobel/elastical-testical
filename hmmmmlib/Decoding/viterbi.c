#include <stdio.h>
#include <stdlib.h>


int viterbi(int n_obs, int n_states, float *start_p, float **trans_p, float **emit_p, int n_data, int *data[]);


int main() {
    // set hardcoded probs
    int n_states = 2; // healthy, fever
    int n_obs = 3; // normal, cold, dizzy

    float start_p_[2] = {0.6, 0.4};
    float* start_p = start_p_; // Hvilken forskel gør den her linje? Måske kan jeg nøjes med et &-tegn ved viterbi(), og udelade denne linje?

    float trans_p_[2][2] = {{0.7, 0.3}, {0.4, 0.6}};
    float** trans_p = calloc(2, sizeof(float*));
    for (int i = 0; i < 2; i++) trans_p[i] = trans_p_[i]; // Hvornår allokerer vi kolonnerne?

    float emit_p_[2][3] = {{0.5, 0.4, 0.1}, {0.1, 0.3, 0.6}}; // [state][obs]
    float** emit_p = calloc(2, sizeof(float*));
    for (int i = 0; i < 2; i++) emit_p[i] = emit_p_[i];
    
    
    
    // feed data to the viterbi alg.

    int n_data = 4; // normal, cold, dizzy, dizzy
    int data_[4] = {0, 1, 2, 2}; // normal, cold, dizzy, dizzy
    int *data = data_;
    


    viterbi(n_obs, n_states, start_p, trans_p, emit_p, n_data, &data);

    


    return 0;
}
 

int viterbi(int n_states, int n_obs, float *start_p, float **trans_p, float **emit_p, int n_data, int *data[]) {



    float* probs = calloc(n_states, sizeof(float)); 
    float max_ = 0.0;

    int hidden_state = -1; // -1 for uninitialized value

    
    for (int i = 0; i < n_data; ++i) {
        if (hidden_state == -1) { 
            // first iteration. Compute only with start_p
            printf("entered initial with i = %d\n", i);

            for (int j = 0; j < n_states-1; j++) {
                probs[j] = start_p[j]*emit_p[j][i];
                printf("%d>%f ", j, probs[j]);

            }
            printf("\n");
        }
        
        else {
            // All iterations after the first.
            printf("entered next with i = %d\n", i);
            
            
            for (int j = 0; j < n_states-1; j++) {
                // For hver state, ønsker vi at beregne ssh. for den nye observation
                ;
                probs[j] = max_ * trans_p[hidden_state][j] * emit_p[j][i];
                //printf("max_ %f, trans_p %f, emit_p %f\n", max_, trans_p[hidden_state][j], emit_p[j][i]);
                printf("%d>%f ", j, probs[j]);
            }

            
        }

        // Find the hidden state
        //float max_ = 0.0;
        max_ = 0.0;
        for (int j = 0; j < n_states-1; j++) {
            if (probs[j] > max_) {
                max_ = probs[j];
                hidden_state = j;
            }
        }
        printf("hs is %i with p = %f\n\n", hidden_state, max_);
        
        //break;
        
    }
    
    return 0;


}