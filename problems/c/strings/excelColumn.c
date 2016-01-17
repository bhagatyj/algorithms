#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* convertToTitle(int n) {
    
    char title[8];
    int i = 7;
    
    title[i--] = 0;
    while ( n > 0 ) {
        title[i--] = 'A' + (( n - 1) % 26);
        n = (n-1) / 26;
    }
    
    return strdup(title+i+1);
    
}

int main() {
    printf("%s\n", convertToTitle(1434) );
}
