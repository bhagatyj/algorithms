#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int rStrStr( char *line, char *s ) {
    int i, j, llen, slen;

    llen = strlen(line); slen = strlen(s);

    for ( i=llen-slen; i>=0; i-- ) {
        for ( j=0; j<slen; j++ ) {
            if ( i+j >= llen ) { break; }
            if ( line[i+j] != s[j] ) { break; }
        }
        if ( j == slen ) {
            return i;
        }
    }
    return -1;
}


int main ( int argc, char **argv ) {
    assert( rStrStr("Hello", "H") == 0 );
    assert( rStrStr("Hello", "l") == 3 );
    assert( rStrStr("Helolo", "lo") == 4 );
    assert( rStrStr("Hello", "llo") == 2 );
    assert( rStrStr("Hello", "o") == 4 );
    assert( rStrStr("Hello", "") == 5 );
    assert( rStrStr("Hello", "R") == -1 );
}


