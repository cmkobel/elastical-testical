#include <stdio.h>

/* count digits, white space, others */

/* Hej Thor. Jeg hygger stadig med at faa styr paa de grundlaeggende ting i c. */

// Hej Carl! Du skal bare tage det stille og roligt vi har ikke travlt! :D Sig bare til hvis du gerne vil snakke om noget :D

// Hej Thor! Tusind tak, hvor er du sød.

#include <stdio.h>
#define MAXLINE 1000


//int arrayLength(char[]);
char reverse(char[], char[]);
char reversed(char[]);

int main() {
    // Den streng jeg faktisk vil reverse.
    char string_[MAXLINE] = "abemade";

    printf("%s", reverse(string_));

    return 0;
}
/*
int arrayLength(char line[]) {
    int rv = 0;
    for (int i = 0; i < MAXLINE && line[i] != '\0'; ++i)
        ++rv;

    return rv;
}
*/

char reverse(char reverse[], char reversed[]) {
    // sets the returned
    
    
    // get length
    int i = 0;
    while (i < MAXLINE && reverse[i] != '\0')
        ++i;

    
    return reversed;


}
