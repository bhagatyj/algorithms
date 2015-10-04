#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int countStrStr( char *line, char *s ) {
    int i, j, llen, slen, count;

    llen = strlen(line); slen = strlen(s); count = 0;

    for ( i=0; i<llen; i++ ) {
        for ( j=0; j<slen; j++ ) {
            if ( i+j >= llen ) { break; }
            if ( line[i+j] != s[j] ) { break; }
        }
        if ( j == slen ) {
            count++;
        }
    }
    return count;
}


int main ( int argc, char **argv ) {
    assert( countStrStr("Hello", "H") == 1 );
    assert( countStrStr("Hello", "l") == 2 );
    assert( countStrStr("Helelo", "el") == 2 );
    assert( countStrStr("Hello", "o") == 1 );
    assert( countStrStr("Hello", "j") == 0 );
    assert( countStrStr("Hello", "llO") == 0 );
}
