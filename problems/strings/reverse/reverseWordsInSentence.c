#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * This function assumes space as the delimiter
 * It also assumes that the delimiter occurs 
 * exactly once between words.
 *
 * The first word is a special case, because there is 
 * no delimiter in front of it. So, when looking for 
 * the delimiter, it is important to make sure that 
 * we do not go before the first char in the sentence.
 *
 * lastPos is used to find the length of the current word.
 * Depending on whether it is first word or not, there could
 * be an off-by-one issue in calculating the length.
 *
 */
void 
reverse( char *start, char *end)
    char tmp;
    while ( start < end ) {
        tmp = *start;
        *start = *end;
        *end = tmp;
        start++; end--;
    }
}

char *
reverseWords( char *input ) {
    char *output = (char *)malloc(sizeof(char)*strlen(input));
    if (!output) { return NULL; }

    strcpy( output, input, strlen(input) );
}

int main ( int argc, char **argv) {
    assert( strcmp( reverseWords("I am a boy"), "boy a am I" ) == 0 );
    assert( strcmp( reverseWords("a boy"), "boy a" ) == 0 );
    assert( strcmp( reverseWords("boy"), "boy" ) == 0 );
    assert( strcmp( reverseWords(""), "" ) == 0 );
}
