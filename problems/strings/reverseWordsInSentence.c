#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char * reverse( char *src ) {
    char *dst, *dstPos, *srcPos, *lastPos;
    int len, wordLen;

    len = strlen(src);
    dst = (char *)malloc(len);
    memset( dst, 0, len );
    srcPos = lastPos = src + len;
    dstPos = dst;

    while ( srcPos > src ) {
        srcPos--;
        while ( *srcPos != ' ' )
            if ( srcPos > src )
                srcPos--;
            else 
                break;
        if ( *srcPos == ' ' ) {
            // Not the first word
            wordLen = lastPos - srcPos - 1;
            lastPos = srcPos;
            strncpy( dstPos, srcPos+1, wordLen );
            dstPos += wordLen;
            *dstPos = ' ';
            dstPos++;
        } else {
            // First word
            wordLen = lastPos - srcPos;
            strncpy( dstPos, srcPos, wordLen );
            dstPos += wordLen;
        }
    }
    *dstPos = '\0';
    dstPos++;
    return dst;
}

int main ( int argc, char **argv) {
    assert( strcmp( reverse("I am a boy"), "boy a am I" ) == 0 );
    assert( strcmp( reverse("a boy"), "boy a" ) == 0 );
    assert( strcmp( reverse("boy"), "boy" ) == 0 );
    assert( strcmp( reverse(""), "" ) == 0 );
}
