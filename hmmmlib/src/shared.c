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

#include "backward.h"
#include "backward.c"

#include "forward.h"
#include "forward.c"

#include "viterbi.h"
#include "viterbi.c"

#include "baumWelch.h"
#include "baumWelch.c"

#include "posteriorDecoding.h"
#include "posteriorDecoding.c"




/* 
int main_test() {
    
    if(testForwardAlgorithm()){
        printf("\nall Forward Algorithm tests succed\n");
    }
   
    if(testBackwardAlgorithm()){
        printf("\nall Backward Algorithm tests succed\n");
    }
    
    if(testBaumWelch()){
        printf("\nall Baum Welch tests succed\n");
    }
    
    if(testViterbi()){
        printf("\nall Viterbi tests succed\n");
    }
    return 0;
}
     */
