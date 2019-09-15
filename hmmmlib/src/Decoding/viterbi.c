#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "viterbi.h"

unsigned int argMax(double* list_, unsigned int n) {
    // Returns the index of the highest element.
    // Would it be faster to use more pointers?  
    double max_value = -INFINITY;
    unsigned int max_index = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (list_[i] > max_value) {
            max_value = list_[i];
            max_index = i;
        }
        printf("%i\n", i);
    }
    return max_index;
}

int* viterbi(HMM *hmm, const int *Y, const int T) {
    // Y is the data, T is the length of the data

    
    
    unsigned int i;
    unsigned int k;
    unsigned int j;
    
    // allocate matrix[data][states]
    double** table = calloc(T, sizeof(double*)); //
    for (i = 0; i < T; ++i) {
        table[i] = calloc(hmm->hiddenStates, sizeof(double));
    }
    
    // Compute initial probabilities
    for (i = 0; i < hmm->hiddenStates; ++i) {
        table[0][i] = hmm->initProbs[i] * hmm->emissionProbs[i*hmm->observations+Y[0]];
    }
    
    // for (int get = 0; get < 7; get++)
    // {
    //     printf("%f ", table[0][get]);
    // }
    // printf("\n");

    // tast argMax
    /* 
    unsigned int length_ = 11;
    double long_array_[11] = {1,2,8,5,7,8,3,7,200, 8, 100};
    unsigned int res = argMax(long_array_, length_);
    printf("max index is %i, which yields value %f", res, long_array_[res]);
     */
    
    
    
    
    
    // Fill the rest of the dynamic programming matrix.
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

    
    
    
    
    
    
    
    // debug print table
    printf("\n");
    for (int row = 0; row < T; row++) {
        for (int col = 0; col < hmm->hiddenStates; col++) {
            printf("%.6f  ", table[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    
    
    
    /* 
    // Backtrack
    unsigned int* z = calloc(T, sizeof(int));
    z[T-1] = argMax(table[T-1] - 1, T);
    for (unsigned int i = T; i > 0; i--) {
        //Husk altid at sige i-1
        printf("%u", i);
        for (unsigned int j = 0; j < hmm->hiddenStates; j++) {
            if (table[i-2][j] + )
        }
        
    } */
    

    
    
    int* dummyoutput = calloc(2, sizeof(int));
    dummyoutput[0] = 32837;
    return dummyoutput;
    
    
    
}
