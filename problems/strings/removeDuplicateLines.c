#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Design Considerations:
 *
 * Storing only the unique lines saves space - esp in cases 
 * where there are large number of duplicate lines in the input.
 *
 * Using strdup to store the string allocates only space needed 
 * for the string passed (as opposed to maxlen)
 *
 * fgets needs pre-allocated space to return the string. Using temp
 * variable for this helps re-use the same space for successive strings
 * and makes the logic look easier.
 *
 * Increasing the number of hash buckets increases the storage
 * space slightly, but can cause very high increase in performance.
 *
 * The hash function used is a simple summation of all the char values.
 *
 */

typedef struct line_data_t_ {
    char * line;
    struct line_data_t_ *next;
} line_data_t;

#define NUM_HASH_BUCKETS 12
#define MAX_LINE_LENGTH 255

int maxLines = 0;
line_data_t *lineDetails[NUM_HASH_BUCKETS];

int hash ( char *line ) {
    int i;
    unsigned sum = 0;

    for (i=0; line[i] != '\0'; i++) {
       sum += line[i]; 
    }
    return (sum % NUM_HASH_BUCKETS);
}
    
int duplicateLine ( char *line ) {
    unsigned h = hash(line);
    line_data_t *ldt = lineDetails[h];

    while ( ldt ) {
        if ( strcmp( ldt->line, line ) == 0 ) {
            return 1;
        }
        ldt = ldt->next;
    }

    return 0;
}

void storeLine(  char *line ) {
    unsigned h = hash(line);
    line_data_t *newLdt = (line_data_t *) malloc(sizeof(line_data_t) );
    char *newLine = strdup(line);

    memset(newLdt, 0, sizeof(line_data_t) );
    newLdt->line = newLine;
    newLdt->next = lineDetails[h];
    lineDetails[h] = newLdt;

    return;
}

int main(int argc, char **argv) {
    char line[MAX_LINE_LENGTH];

    if ( argc != 2 ) {
        printf("usage: %s <filename> \n", argv[0] );
        exit(1);
    }
    FILE *fp = fopen( argv[1], "r" );
    if ( fp == NULL ) {
        printf( " Could not open file: %s\n", argv[1] );
    }
    while ( fgets( line, MAX_LINE_LENGTH, fp )  ) {
        if ( ! duplicateLine( line )  ) {
            storeLine( line );
            printf( "%s", line );
        }
    }
    return 0;
}
 
