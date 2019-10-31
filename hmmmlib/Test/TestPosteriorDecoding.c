#include "TestPosteriorDecoding.h"


#include "posteriorDecoding.h"


#include "hmm.h"


#include <stdlib.h>
#include <assert.h>



extern bool testPosteriorDecoding() {
    HMM * hmm = HMMCreate(7, 4);
    

    double initProbs[7] = {0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00};
    
    
    double transitionProbs[7][7] ={
        {0.00, 0.00, 0.90, 0.10, 0.00, 0.00, 0.00},
        {1.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.05, 0.90, 0.05, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 1.00},
        {0.00, 0.00, 0.00, 0.10, 0.90, 0.00, 0.00},
    };
    
    double emissionProbs[7][4] = {
        {0.30, 0.25, 0.25, 0.20},
        {0.20, 0.35, 0.15, 0.30},
        {0.40, 0.15, 0.20, 0.25},
        {0.25, 0.25, 0.25, 0.25},
        {0.20, 0.40, 0.30, 0.10},
        {0.30, 0.20, 0.30, 0.20},
        {0.15, 0.30, 0.20, 0.35}
    };
    
    unsigned int data[105] =     {0, 1, 3, 3, 2, 1, 2, 3, 0, 0, 1, 2, 1, 0, 2, 3, 0, 1, 3, 1, 2, 0, 3, 1, 2, 0, 3, 1, 2, 3, 0, 1, 2, 1, 0, 3, 2, 1, 0, 0, 1, 0, 3, 2, 0, 3, 0, 0, 0, 3, 1, 1, 0, 0, 3, 1, 0, 3, 1, 0, 3, 0, 1, 0, 3, 2, 0, 1, 0, 3, 1, 0, 2, 1, 3, 0, 2, 1, 0, 3, 2, 0, 1, 2, 0, 3, 1, 0, 2, 3, 0, 1, 2, 0, 1, 3, 0, 1, 2, 0, 3, 1, 2, 3, 0};
    unsigned int expected[105] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0};
    unsigned int * data_ = data;
    unsigned int data_len = 105;

    //unsigned int * result = posteriorDecoding(hmm, data_, data_len);
    double * result = posteriorDecoding(hmm, data_, data_len);
    

    

    // debug print output from algorithm
    for (unsigned int i = 0; i < data_len; i++) {
        //printf("%d ", result[i]);
        //printf("%f ", result[i]);
        ;
        
        
    }
    

    return true;
}
