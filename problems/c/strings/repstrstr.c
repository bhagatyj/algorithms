#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int replace( char *line, char *pattern, char *replace ) {
    int i, j, llen, plen, rlen, count;

    llen = strlen(line); 
    plen = strlen(pattern); 
    rlen = strlen(replace); 
    count = 0;
    if (rlen != plen) {
        return -1;
    }

    for ( i=0; i<=llen-plen; i++ ) {
        for ( j=0; j<plen; j++ ) {
            if ( line[i+j] != pattern[j] ) { break; }
        }
        if ( j == plen ) {
            for ( j=0; j<plen; j++ ) {
                line[i+j] = replace[j];
            }
            i += plen-1;
            count++;
        }
    }
    return count;
}


int main ( int argc, char **argv ) {
    char line[] = "Hello, how are you, how is life ? Is everything ok ?";
    
    assert( replace(line, "how", "who" ) == 2);
    assert( strcmp( line, "Hello, who are you, who is life ? Is everything ok ?" ) == 0);
    assert( replace(line, "h", "w" ) == 3);
    assert( strcmp( line, "Hello, wwo are you, wwo is life ? Is everytwing ok ?" ) == 0);
}


