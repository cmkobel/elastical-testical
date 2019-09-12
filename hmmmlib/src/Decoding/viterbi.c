#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "viterbi.h"

int* viterbi(HMM *hmm, const int *Y, const int T) {
    
    
    //Det virker fint at tage log til et bestemt tal:
    
    printf("Det virker fint at tage log til et bestemt tal: log(e) = %f\n", log(2.71828));
    
    //Nu prøver jeg at putte værdien ind i en pladsholder-varibel:
    double pladsholder = hmm->emissionProbs[0];
    printf("Det hjælper ingenting. %f", log(pladsholder));
    
    
    unsigned int i;
    unsigned int k;
    unsigned int j;
    
    // table[data][states]
    double** table = calloc(T, sizeof(double*));
    for (i = 0; i < T; ++i) {
        table[i] = calloc(hmm->hiddenStates, sizeof(double));
    }
    
    // base
    for (i = 0; i < hmm->hiddenStates; ++i) {
        table[0][i] = hmm->initProbs[i] * hmm->emissionProbs[i*hmm->observations+Y[0]];
    }
    
    // for (int get = 0; get < 7; get++)
    // {
    //     printf("%f ", table[0][get]);
    // }
    // printf("\n");
    
    
    
    
    for (i = 1; i < T; ++i) {
        for (k = 0; k < hmm->hiddenStates; ++k) {
            float value = 0;
            for (j = 0; j < hmm->hiddenStates; ++j) {
                if (table[i-1][j] * hmm->transitionProbs[j*hmm->hiddenStates+k] > value) {
                    value = table[i-1][j] * hmm->transitionProbs[j*hmm->hiddenStates+k];
                }
            }
            table[i][k] = hmm->emissionProbs[k*hmm->observations+Y[i]] * value;
        }
    }
    
    
    
    
    
    
    
    /*
    // debug print table
    printf("\n");
    for (int row = 0; row < T; row++)
    {
        for (int col = 0; col < hmm->hiddenStates; col++)
        {
            printf("%.6f  ", table[row][col]);
        }
        printf("\n");
        
    }
    printf("\n");
    */
    
    int* dummyoutput = calloc(2, sizeof(int));
    dummyoutput[0] = 32837;
    return dummyoutput;
    
    
    
}
