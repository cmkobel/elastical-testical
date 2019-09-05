#include <stdio.h>
#include <stdlib.h>


int viterbi(int n_obs, int n_states, double start_p, double *trans_p, double *emit_p);

int main() {
    // set hardcoded probs
    int n_obs = 3; // normal, cold, dizzy
    int n_states = 2; // healthy, fever
    double start_p_[2] = {0.6, 0.4};
    
    double trans_p_[2][2] = {{0.7, 0.3}, {0.4, 0.6}};
    double (*trans_p)[2] = trans_p_; // make a pointer to the first element
    
    double emit_p_[2][3] = {{0.5, 0.4, 0.1}, {0.1, 0.3, 0.6}};
    double (*emit_p)[3] = emit_p_; // make a pointer to the first element


    // printf("%f\n", emit_p[1][1]);


    viterbi(n_obs, n_states, *start_p_, *trans_p, *emit_p);



    return 0;
}


int viterbi(int n_obs, int n_states, double start_p, double *trans_p, double *emit_p) {

    double rv;
    rv = 0.0;

    int observations[] = {0, 1 ,2}; // normal, cold, dizzy
    int n_observations = 3;


    return rv;


}