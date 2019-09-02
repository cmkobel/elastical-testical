#include <stdio.h>

/* count digits, white space, others */

/* Hej Thor. Jeg hygger stadig med at faa styr paa de grundlaeggende ting i c. */

// Hej Carl! Du skal bare tage det stille og roligt vi har ikke travlt! :D Sig bare til hvis du gerne vil snakke om noget :D

// Hej Thor! Tusind tak, hvor er du sød.

int power(int, int); /* function prototype */

int main() {
    int i;

    for (i = 0; i < 100; i = i + 1)
        printf("%d %d %d\n", i, power(2, i), power(-3, i));
    return 0;

    /* power: raise base to n-th power; n >= 0 */
    

}

int power(int base, int n) {
        int i, p;

        p = 1;
        for (i = 1; i <=n ; ++i)
            p = p * base;
        return p;

    }
