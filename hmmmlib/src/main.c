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
#include <Accelerate/Accelerate.h>

int main() {
    
    double inVector1[2] = {1,1};
    double inVector2[2] = {1,1};
    double result = cblas_ddot(2, inVector1, 1, inVector2, 1);
    
    printf("%f\n", result);
    
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
    
