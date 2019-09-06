#include "posteriorDecoding.h"

int posteriorDecoding(HMM * hmm, const int *Y, const int T, const int t){
    
    int index = 0;
    unsigned int i;
    unsigned int j;
    
    double ** alpha = forward(hmm, Y, T);
    double ** beta = backward(hmm, Y, T);
    
    double largest = 0.0;
    double denominator = 0.0;
    
    for(j = 0; j < hmm->hiddenStates; j++){
        denominator += alpha[j][t]*beta[j][t];
    }
    
    for (i = 0; i < hmm->hiddenStates; i++) {
        
        double numerator = alpha[i][t]*beta[i][t];
        double gamma = numerator/denominator;
        
        if(gamma > largest){
            index = i;
            largest = gamma;
        }
    }
    
    return 1;
}
