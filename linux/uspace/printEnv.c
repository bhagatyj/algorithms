#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    char **env;

    for (env = envp; *env; env++) {
        printf("%s\n", *env);
    }
}

