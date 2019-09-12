//
//  main.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 29/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include <stdio.h>
#include "hmm.h"
#include "TestsForwardAlgorithm.h"
#include "testBackwardAlgorithm.h"
#include "TestBaumWelch.h"

int main() {
    
    /*
     Testing the forward algorithm
     
    if(testForwardAlgorithm()){
        printf("all Forward Algorithm tests succed\n");
    }
   */
    /*
     Testing the backward algorithm
    */
    if(testBackwardAlgorithm()){
        printf("all Backward Algorithm tests succed\n");
    }
    /*
     Testing the backward algorithm
     
    if(testBaumWelch()){
        printf("all Baum Welch tests succed\n");
    }
    */
    return 0;
}
