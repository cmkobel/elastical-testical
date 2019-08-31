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

int main() {
    
    bool forwardAlgorithmTests = testForwardAlgorithm();
    
    if(forwardAlgorithmTests){
        printf("all tests succed\n");
    }
    
    return 0;
}
