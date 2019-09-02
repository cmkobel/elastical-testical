//
//  main.c
//  hmmmmlib
//
//  Created by Thor Jakobsen on 29/08/2019.
//  Copyright © 2019 Thor Jakobsen. All rights reserved.
//

#include <stdio.h>
#import "hmm.h"
#import "TestsForwardAlgorithm.h"
#import "testBackwardAlgorithm.h"

int main() {
    
    /*
     Testing the forward algorithm
     */
    if(testForwardAlgorithm()){
        printf("all Forward Algorithm tests succed\n");
    }
   
    /*
     Testing the backward algorithm
    if(testBackwardAlgorithm()){
        printf("all Backward Algorithm tests succed\n");
    }
     */
    
    return 0;
}
