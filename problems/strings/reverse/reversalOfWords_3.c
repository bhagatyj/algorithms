#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
reverse( char *src, char *dst ) {
    while ( src < dst ) {
        char tmp;
        tmp = *src;
        *src = *dst;
        *dst = tmp;
        src++; dst--;
    }
}

char *
reverseWords( char *input ) {
    char *start = input;
    int length = strlen(input);

    reverse( start, start+length-1 );
    
    char *wordEnd = start;
    while( *wordEnd ) {
        wordEnd++;
        if(( *wordEnd == ' ' ) ||
           ( *wordEnd == 0 ) ) {
            reverse( start, wordEnd-1 );
            // Take care of extra spaces
            while( *wordEnd == ' ' ) { wordEnd++; }
            start = wordEnd+1;
        }
    }
    return input;
}

int
main() {
    printf("%s\n", reverseWords( strdup( "I am a boy" ) ) );
    printf("%s\n", reverseWords( strdup( "I  am a  boy" ) ) );
}
