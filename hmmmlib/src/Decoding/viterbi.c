#include <stdio.h>
#include <stdlib.h>
#include "viterbi.h"

int* viterbi(HMM *hmm, const int *observations, const int nData) {                    
    
    unsigned int i;
    unsigned int k;
    unsigned int j;

    // table[data][states]
    double** table = calloc(nData, sizeof(double*));
    for (i = 0; i < nData; ++i) {
        table[i] = calloc(hmm->hiddenStates, sizeof(double));
    }
    
    // base
    for (i = 0; i < hmm->hiddenStates; ++i) {
        table[0][i] = hmm->initProbs[i] * hmm->emissionProbs[i][observations[0]];
    }

    // for (int get = 0; get < 7; get++)
    // {
    //     printf("%f ", table[0][get]); 
    // }
    // printf("\n");
    
    

    
    for (i = 1; i < nData; ++i) {
        for (k = 0; k < hmm->hiddenStates; ++k) {
            float value = 0;
            for (j = 0; j < hmm->hiddenStates; ++j) {
                if (table[i-1][j] * hmm->transitionProbs[j][k] > value) {
                    value = table[i-1][j] * hmm->transitionProbs[j][k];
                    
                }
            }
            table[i][k] = hmm->emissionProbs[k][observations[i]] * value;
            

            

        }
    }
    

     





    // debug print table
    printf("\n");
    for (int row = 0; row < nData; row++)
    {
        for (int col = 0; col < hmm->hiddenStates; col++)
        {
            printf("%f, ", table[row][col]);
        }
        printf("\n");
        
    }
    printf("\n");
    

    int* dummyoutput = calloc(2, sizeof(int));
    dummyoutput[0] = 32837;
    return dummyoutput;



}