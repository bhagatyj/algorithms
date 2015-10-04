#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int countStrStr( char *line, char *s ) {
    int i, j, llen, slen, count;

    llen = strlen(line); slen = strlen(s); count = 0;

    for ( i=0; i<=llen-slen; i++ ) {
        for ( j=0; j<slen; j++ ) {
            if ( line[i+j] != s[j] ) { break; }
        }
        if ( j == slen ) {
            count++;
        }
    }
    return count;
}

char * replace( char *line, char *pattern, char *replace) {
    int i, j, k, llen, plen, rlen, count;
    char *newline;

    count = countStrStr(line, pattern);
    llen = strlen(line); 
    plen = strlen(pattern); 
    rlen = strlen(replace); 

    if (rlen != plen) {
        newline = malloc( llen + count*(rlen-plen) );
        if ( !newline ) {
            return NULL;
        }
        memset(newline, 0, llen + count*(rlen-plen) );
    } else {
        newline = line;
    }

    for ( i=0, k=0; i<=llen-plen; i++,k++ ) {
        for ( j=0; j<plen; j++ ) {
            if ( line[i+j] != pattern[j] ) { break; }
        }
        if ( j == plen ) {
            for ( j=0; j<rlen; j++ ) {
                newline[k+j] = replace[j];
            }
            i += plen-1;
            k += rlen-1;
            count++;
        } else {
            newline[k] = line[i];
        }
    }
    for ( i=llen-plen+1; i<llen; i++,k++ ) {
        newline[k] = line[i];
    }
    newline[k] = '\0';
    return newline;
}

int main ( int argc, char **argv ) {
    char line[] = "Hello, how are you, how is life ? Is everything ok ?";
    char *nline;
    char *expected;
    
    nline = replace(line, "how", "who" );
    expected = "Hello, who are you, who is life ? Is everything ok ?";
    assert(strcmp( nline, expected ) == 0 );

    nline = replace(nline, "h", "w" );
    expected = "Hello, wwo are you, wwo is life ? Is everytwing ok ?";
    assert(strcmp( nline, expected ) == 0 );

    nline = replace(nline, "f", "iww" );
    expected = "Hello, wwo are you, wwo is liiwwe ? Is everytwing ok ?";
    assert(strcmp( nline, expected ) == 0 );

    nline = replace(nline, "w", "tiss" );
    assert( strcmp( nline, "Hello, tisstisso are you, tisstisso is liitisstisse ? Is everyttissing ok ?" ) == 0);
}


