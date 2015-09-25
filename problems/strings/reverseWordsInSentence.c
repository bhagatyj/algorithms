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
