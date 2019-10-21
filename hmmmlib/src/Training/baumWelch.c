#include "baumWelch.h"
#include <stdlib.h>

void baumWelch(HMM *hmm, const unsigned int *Y, const unsigned int T, const int itterations){
    
    //Initial random init of HMM
    
    unsigned int i;
    unsigned int j;
    unsigned int l;
    
    // Gamma 2d matrix
    //
    // [time][state]
    //
    double * gamma = calloc(T*hmm->hiddenStates, sizeof(double));
    
    // Xi 3d matrix
    //
    // [state][state][time]
    //
    double * xi = calloc(hmm->hiddenStates*hmm->hiddenStates*T, sizeof(double));
    
    for(int q = 0; q < itterations; q++) {
        double * scaleFactor = calloc(T, sizeof(double));
        double * alpha = forward(hmm, Y, T, scaleFactor);
        double * beta = backward(hmm, Y, T, scaleFactor);
        
        // Updating gamma
        for(i = 0; i < T; i++){
            for (j = 0; j < hmm->hiddenStates; j++) {
                double numerator = alpha[i*hmm->hiddenStates+j]*beta[(T-i-1)*hmm->hiddenStates+j];
                //printf("%f, %f -> ",alpha[i*hmm->hiddenStates+j], beta[i*hmm->hiddenStates+j]);
                double denominator = 0.0;
                for(l = 0; l < hmm->hiddenStates; l++){
                    denominator += alpha[i*hmm->hiddenStates+l]*beta[(T-i-1)*hmm->hiddenStates+l];
                }
                //printf("Numerator:%f - Denominator:%f\n", numerator, denominator);
                gamma[i*hmm->hiddenStates+j] = numerator/denominator;
            }
        }
        
        printf("Gamma\n");
        for(i = 0; i < T; i++) {
            for (j = 0; j < hmm->hiddenStates; j++){
                printf("%f, ", gamma[i*hmm->hiddenStates+j]);
            }
            printf("\n");
        }
        printf("\n");
       
        
        // xi denominator
        double * xiDenominator = calloc(T-1, sizeof(double));
        
        for(l = 0; l < T-1; l++){
            for(i = 0; i < hmm->hiddenStates; i++){
                for(j = 0; j < hmm->hiddenStates; j++){
                    xiDenominator[l] += alpha[l*hmm->hiddenStates+i]*beta[(T-l-2)*hmm->hiddenStates+j]*hmm->transitionProbs[i*hmm->hiddenStates+j]*hmm->emissionProbs[j*hmm->observations+Y[l+1]];
                }
            }
            printf("XI denominator: %f\n", xiDenominator[l]);
        }
        
        // Updating xi
        for(i = 0; i < hmm->hiddenStates; i++){
            for(j = 0; j < hmm->hiddenStates; j++){
                for(l = 0; l < T-1; l++){
                    double numerator = alpha[l*hmm->hiddenStates+i]*beta[(T-l-2)*hmm->hiddenStates+j]*hmm->transitionProbs[i*hmm->hiddenStates+j]*hmm->emissionProbs[j*hmm->observations+Y[l+1]];
                    double denominator = xiDenominator[l];
                    xi[i*hmm->hiddenStates*T+j*T+l] = numerator/denominator;
                }
            }
        }
        
        //Updating initial probs
        for (i = 0; i < hmm->hiddenStates; i++) {
            hmm->initProbs[i] = gamma[i];
        }
        
        //Updating transition probs
        for (i = 0; i < hmm->hiddenStates; i++) {
            for (j = 0; j < hmm->hiddenStates; j++) {
                double xiSum = 0.0;
                double gammaSum = 0.0;
                for(l = 0; l < T-1; l++){
                    xiSum += xi[i*hmm->hiddenStates*T+j*T+l];
                    gammaSum += gamma[l*hmm->hiddenStates+i];
                }
                hmm->transitionProbs[i*hmm->hiddenStates+j] = xiSum/gammaSum;
            }
        }
        
        //Updating observations probs
        for (i = 0; i < hmm->hiddenStates; i++) {
            for (j = 0; j < hmm->observations; j++) {
                double numerator = 0.0;
                double denominator = 0.0;
                for(l = 0; l < T; l++){
                    if(Y[l] == j){
                        numerator += gamma[l*hmm->hiddenStates+i];
                    }
                    denominator += gamma[l*hmm->hiddenStates+i];
                }
                hmm->emissionProbs[i*hmm->observations+j] = numerator/denominator;
            }
        }
        
        //Normalization step
        for(i = 0; i < hmm->hiddenStates; i++){
            double sum = 0.0;
            for (j = 0; j < hmm->hiddenStates; j++) sum += hmm->transitionProbs[i*hmm->hiddenStates+j];
            for (j = 0; j < hmm->hiddenStates; j++) hmm->transitionProbs[i*hmm->hiddenStates+j] = hmm->transitionProbs[i*hmm->hiddenStates+j]/sum;
            sum = 0.0;
            for (j = 0; j < hmm->observations; j++) sum += hmm->emissionProbs[i*hmm->observations+j];
            for (j = 0; j < hmm->observations; j++) hmm->emissionProbs[i*hmm->observations+j] = hmm->emissionProbs[i*hmm->observations+j]/sum;
        }
    }
}

// Asign random variables to all initprobs, transprobs and obsprobs
void assignRandomValues(HMM *hmm){
    
    
    
}
