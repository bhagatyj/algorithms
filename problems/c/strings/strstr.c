#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int myStrstr2( char *src, char *search ) {

    char *posLine, *posSearch, *end, *endSearch, *start;

    start = src;
    end = start + strlen(start);
    endSearch = search + strlen(search);

    while ( start < end ) {
        posLine = start;
        posSearch = search;
        while ( posSearch < endSearch ) {
            if ( *posSearch != *posLine ) {
                break;
            }
            posSearch++; posLine++;
        }
        // match has been found if we are at the end
        // of the search string (null char)
        if ( posSearch == endSearch ) {
            return ( start - src );
        }
        // Couldnt find search in this start position.
        // Try the next one.
        start++;
    }
    return -1;
}

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


