// Problem: Implement string rotateString(string input, int amt)
// Right shift

#include <stdio.h>
#include <string.h>
#include <assert.h>

// Space efficient. But slow
char * rotateStr( char *s, int num ) {
    int len = strlen(s);
    char lastChar;
    int i, j;

    // This step makes sure that a 50K rotation on a 
    // 10-char string is fast.
    num = num % len;

    for (j = 0; j< num; j++) {
        lastChar = s[len-1];
        for ( i=len-1; i>0; i--) {
            s[i] = s[i-1];
        }
        s[0] = lastChar;
    }
    return s;
}

char * rotateStrFast( char *s, int num) {
}

int main(int argc, char **argv) {

    char * result;
    char qn[] = "abc";

    result = rotateStr( qn, 1 );
    printf("%s\n", result);
    assert ( strcmp( result, "cab" ) == 0);

    result = rotateStr( result, 0 );
    printf("%s\n", result);
    assert ( strcmp( result, "cab" ) == 0);
    result = rotateStr( result, 3 );
    printf("%s\n", result);
    assert ( strcmp( result, "cab" ) == 0);
    result = rotateStr( result, 2 );
    printf("%s\n", result);
    assert ( strcmp( result, "abc" ) == 0);
}
