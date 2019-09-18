#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "viterbi.h"

unsigned int argMax(double* list_, unsigned int n) {
    // Returns the index of the highest element.
    // Would it be faster to use more pointers?  
    double max_value = -INFINITY;
    unsigned int max_index = 0;
    double dbg1;
    for (unsigned int i = 0; i < n; i++) {
        dbg1 = list_[i];
        if (list_[i] > max_value) {
            max_value = list_[i];
            max_index = i;
        }
        //printf("%i\n", i);
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
            float value = -INFINITY;
            for (j = 0; j < hmm->hiddenStates; ++j) {
                if (table[i-1][j] + log(hmm->transitionProbs[j*hmm->hiddenStates+k]) > value) {
                    value = table[i-1][j] + log(hmm->transitionProbs[j*hmm->hiddenStates+k]);
                }
            }
            table[i][k] = log(hmm->emissionProbs[k*hmm->observations+Y[i]]) + value;
        }
    }

    
    
    
    
    
    
    
    // debug print table
    printf("\n");
    for (int row = 0; row < T; row++) {
        for (int col = 0; col < hmm->hiddenStates; col++) {
            printf("%9.3f  ", table[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    
    
    // Der er noget galt med den måde argMax læser den liste den får. 
    // Den skal returnene 3, det gør python i hvert fald.
    // Jeg vil starte med at tage et skridt af vejen fra læsningen af table[T-1] 
    // til den bliver givet til argMax og beregnet. Og se hvad der sker 
    // på vejen.

    for (unsigned int idx = 0; idx < T; idx++)
    {
        printf(" idx: %f", table[T-1][idx]);
    }
    printf("\n");
    
    
    // Backtrack
    unsigned int* z = calloc(T, sizeof(int));
    z[T-1] = argMax(table[T-1], hmm->hiddenStates); // havde jeg ikke en minus 1 for meget her?
    printf("max = %u\n", argMax(table[T-1], hmm->hiddenStates));
    for (unsigned int i = T-1; i > 0; i--) {
        printf("i = %u\n", i);
        

        for (unsigned int j = 0; j < hmm->hiddenStates; j++) {
            printf(" j = %u\n", j);
                

            float a = table[i-1][j];
            float b = log(hmm->transitionProbs[j*hmm->hiddenStates + z[i]]);
            float c = log(hmm->emissionProbs[z[i]*hmm->observations + Y[i]]);
            float d = table[i][z[i]];
                      
            printf("  a = %f, b = %f, c = %f\n", a, b, c);
            printf("  a + b + c = %f\n", a + b + c);
            printf("  d = %f\n", d);
            
            

            
            if (table[i-1][j] + log(hmm->transitionProbs[j*hmm->hiddenStates + z[i]]) + log(hmm->emissionProbs[z[i]*hmm->observations + Y[i]]) == table[i][z[i]]) {
                printf("   a + b + c == d\n");
                z[i-1] = j;
                break;
            }
        }
        
    }
    

    
    
    /* unsigned int* dummyoutput = calloc(2, sizeof(int));
    dummyoutput[0] = 32837;
    return dummyoutput;
     */
    return z;

    
}
