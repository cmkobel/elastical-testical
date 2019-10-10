//
//  main.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 29/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include <stdio.h>

#include "hmm.h"
#include "hmm.c"

#include "TestsForwardAlgorithm.h"
#include "TestsForwardAlgorithm.c"


#include "testBackwardAlgorithm.h"
#include "testBackwardAlgorithm.c"


#include "TestBaumWelch.h"
#include "TestBaumWelch.c"


#include "TestViterbi.h"
#include "TestViterbi.c"

#include "posteriorDecoding.h"
#include "posteriorDecoding.c"

int main_test();

int main_test() {
    
    /*
     Testing the forward algorithm
     */
    if(testForwardAlgorithm()){
        printf("\nall Forward Algorithm tests succed\n");
    }
   
    /*
     Testing the backward algorithm
    */
    if(testBackwardAlgorithm()){
        printf("\nall Backward Algorithm tests succed\n");
    }
    /*
     Testing the backward algorithm
     */
    if(testBaumWelch()){
        printf("\nall Baum Welch tests succed\n");
    }
    /*
     Testing the viterbi algorithm
     */
    if(testViterbi()){
        printf("\nall Viterbi tests succed\n");
    }
    return 0;
}
    
