#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Notes:
// The first loop needs to go till <= llen-slen.
// There is no need to go further than that as the
// second string would not fit after that...
// 
// The check for match is simply if inner loop reached
// its end.
// 
int myStrstr( char *line, char *s ) {
    int i, j, llen, slen;

    llen = strlen(line); slen = strlen(s);

    for ( i=0; i<=llen-slen; i++ ) {
        for ( j=0; j<slen; j++ ) {
            if ( line[i+j] != s[j] ) { break; }
        }
        if ( j == slen ) {
            return i;
        }
    }
    return -1;
}


int main ( int argc, char **argv ) {
    assert( myStrstr("Hello", "H") == 0 );
    assert( myStrstr("Hello", "llo") == 2 );
    assert( myStrstr("Hello", "o") == 4 );
    assert( myStrstr("Hello", "") == 0 );
    assert( myStrstr("Hello", "R") == -1 );
}


