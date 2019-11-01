//
//  main.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 29/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//


#include <stdio.h>

#include "TestsForwardAlgorithm.h"
#include "testBackwardAlgorithm.h"
#include "TestBaumWelch.h"
#include "TestViterbi.h"
#include "TestPosteriorDecoding.h"

int main() {
    
    /*
     Testing the forward algorithm
     */
    if(testForwardAlgorithm()){
        printf("\nall Forward Algorithm tests succeeded\n");
    }

    /*
     Testing the backward algorithm
    */
    if(testBackwardAlgorithm()){
        printf("\nall Backward Algorithm tests succeeded\n");
    }
    /*
     Testing the backward algorithm
     */
    if(testBaumWelch()){
        printf("\nall Baum Welch tests succeeded\n");
    }
    /*
     Testing the viterbi algorithm
     */
    if(testViterbi()){
        printf("\nall Viterbi tests succeeded\n");
    }
// IKKE COMMIT ÆNDRINGER DER IKKE VIRKER!!!!!!!!
//    if(testPosteriorDecoding()){
//        printf("\nall (none) Posterior Decoding tests succeeded\n");
//    }
    
    return 0;
}
    
