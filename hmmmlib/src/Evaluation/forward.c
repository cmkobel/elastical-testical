#include "forward.h"
#include <stdlib.h>
#include <Accelerate/Accelerate.h>

double * forward(HMM *hmm, const int *Y, const int T, double * scalingFactor){
    
    unsigned int i;
    unsigned int j;
    
    //Creating the emission probs m*n into m, n*n matrix
    double ** new_emission_probs = calloc(hmm->observations, sizeof(double *));
    for(i = 0; i < hmm->observations; i++){
        double * matrix = calloc(hmm->hiddenStates*hmm->hiddenStates, sizeof(double));
        for(j = 0; j < hmm->hiddenStates; j++){
            matrix[j*hmm->hiddenStates+j] = hmm->emissionProbs[j*hmm->observations+i];
        }
        new_emission_probs[i] = matrix;
    }
    
    double * result = calloc(hmm->hiddenStates, sizeof(double));
    // Doing the matrix multiplication
    cblas_dsymv(CblasRowMajor, 121, hmm->hiddenStates, 1.0, new_emission_probs[Y[0]], hmm->hiddenStates, hmm->initProbs, 1, 1, result, 1);
    // Scaling
    cblas_dscal(hmm->hiddenStates, (1.0/cblas_dasum(hmm->hiddenStates, result, 1)), result, 1);
    
    for(i = 0; i < hmm->hiddenStates; i++){
        printf("%f, ", result[i]);
    }
    
    cblas_dgemv(CblasRowMajor, CblasTrans, hmm->hiddenStates, hmm->hiddenStates, 1.0, hmm->transitionProbs, hmm->hiddenStates, result, 1, 0, result, 1);
    cblas_dgemv(CblasRowMajor, CblasTrans, hmm->hiddenStates, hmm->hiddenStates, 1.0, new_emission_probs[Y[1]], hmm->hiddenStates, result, 1, 0, result, 1);
    cblas_dscal(hmm->hiddenStates, (1.0/cblas_dasum(hmm->hiddenStates, result, 1)), result, 1);
    
    for(i = 0; i < hmm->hiddenStates; i++){
        printf("%f, ", result[i]);
    }
    

    // 2D alpha matrix
    //
    // [state][time]
    //
    double * alpha = calloc(hmm->hiddenStates*T, sizeof(double));

    // Initial is the same as the initProbs times the probs of emitting Y[0]
    for(i = 0; i < hmm->hiddenStates; i++){
        alpha[i*T] = hmm->initProbs[i]*hmm->emissionProbs[i*hmm->observations+Y[0]];
        scalingFactor[0] += alpha[i*T+0];
    }
    
    // Scaling step
    for(j = 0; j < hmm->hiddenStates; j++){
        alpha[j*T+0] = alpha[j*T+0]/scalingFactor[0];
    }

    // Now the "recursive" step starts
    for(i = 1; i < T; i++){
        for(j = 0; j < hmm->hiddenStates; j++){
            double emissionProb = hmm->emissionProbs[j*hmm->observations+Y[i]];
            if(emissionProb > 0){
                double pastTransProb = 0.0;
                for(int l = 0; l < hmm->hiddenStates; l++){
                    pastTransProb += hmm->transitionProbs[l*hmm->hiddenStates+j]*alpha[l*T+i-1];
                }
                alpha[j*T+i] = emissionProb*pastTransProb;
            }
            scalingFactor[i] += alpha[j*T+i];
        }
        // Scaling step
        for(j = 0; j < hmm->hiddenStates; j++){
            alpha[j*T+i] = alpha[j*T+i]/scalingFactor[i];
        }
    }
    
    printf("\n\n");
    for(i = 0; i < hmm->hiddenStates; i++) {
        for (j = 0; j < T; j++){
            printf("%f, ", alpha[i*T+j]);
        }
        printf("\n");
    }
    printf("\n");
    
    return alpha;
}
