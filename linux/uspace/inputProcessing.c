#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {

    char *line = NULL;
    size_t line_size = 0;
    FILE *fp;

    fp = fopen("stats.txt", "r");
    while ( getline( &line, &line_size, fp) > 0 ) {
        printf("Line : %s", line);
    }
    free(line);
}

