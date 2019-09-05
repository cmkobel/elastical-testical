#include <stdio.h>
#include <stdlib.h>


int viterbi(int obs, int states, double start_p, double *trans_p, double *emit_p);

int main() {
    int obs = 3; // normal, cold, dizzy
    int states = 2; // healthy, fever
    double start_p_[2] = {0.6, 0.4};
    double trans_p_[2][2] = {{0.7, 0.3}, {0.4, 0.6}};
    double emit_p_[2][3] = {{0.5, 0.4, 0.1}, {0.1, 0.3, 0.6}};
    
    // make compatible pointer types.
    double * start_p = start_p_; 
    double ** trans_p = calloc(2, sizeof(double));
    for(int i = 0; i < 2; i++) trans_p[i] = calloc(2, sizeof(double));

    double ** emit_p = calloc(2, sizeof(double));
    for (int i = 0; i < 2; i++) emit_p[i] = calloc(2, sizeof(double));

    


    viterbi(obs, states, *start_p, *trans_p, *emit_p);



    return 0;
}


int viterbi(int obs, int states, double start_p, double *trans_p, double *emit_p) {

    double rv;
    rv = 0.0;

    printf("day 1:\n%f", rv);

    return rv;


}




