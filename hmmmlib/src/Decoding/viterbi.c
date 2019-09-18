#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "viterbi.h"

unsigned int arrayMax(double* array, unsigned int n) {
    // Returns the index of the maximum element.
    // Would it be faster to use more pointers?  
    double maximum = -INFINITY;
    unsigned int max_index = 0;
    for (unsigned int i = 0; i < n; i++) {
        if (array[i] > maximum) {
            maximum = array[i];
            max_index = i;
        }
    }
    return max_index;
}

unsigned int* viterbi(HMM *hmm, const int *Y, const int T) {
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
        table[0][i] = log(hmm->initProbs[i]) + log(hmm->emissionProbs[i*hmm->observations+Y[0]]);
    }

    
    // Fill the table
    for (i = 1; i < T; ++i) { 
        for (k = 0; k < hmm->hiddenStates; ++k) {
            double value = -INFINITY;
            for (j = 0; j < hmm->hiddenStates; ++j) {
                if (table[i-1][j] + log(hmm->transitionProbs[j*hmm->hiddenStates+k]) > value) {
                    value = table[i-1][j] + log(hmm->transitionProbs[j*hmm->hiddenStates+k]);
                }
            }
            table[i][k] = log(hmm->emissionProbs[k*hmm->observations+Y[i]]) + value;
        }
    }


    // debug print table
    if (false) { 
        printf("\n");
        for (int row = 0; row < T; row++) {
            for (int col = 0; col < hmm->hiddenStates; col++) {
                printf("%9.3f  ", table[row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }    
    
    
    // Backtrack
    unsigned int* decodedStates = calloc(T, sizeof(int));
    decodedStates[T-1] = arrayMax(table[T-1], hmm->hiddenStates); // havde jeg ikke en minus 1 for meget her?
    for (unsigned int i = T-1; i > 0; i--) {
        for (unsigned int j = 0; j < hmm->hiddenStates; j++) {            
            if (table[i-1][j] + log(hmm->transitionProbs[j*hmm->hiddenStates + decodedStates[i]]) + log(hmm->emissionProbs[decodedStates[i]*hmm->observations + Y[i]]) == table[i][decodedStates[i]]) {
                decodedStates[i-1] = j;
                break;
            }
        }
        
    }
    

    return decodedStates;

    
}
