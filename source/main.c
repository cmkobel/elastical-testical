#include <stdio.h>
#include "hmm.c"

int main() {
    /*HMM * objectieMcObjectyface;
    objectieMcObjectyface = HMMCreate(3, 3, 3.0);*/
    

    int c, nl;
    nl = 0;

    
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++nl;
    printf("%d\n", nl);


    return 0;

}