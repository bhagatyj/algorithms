#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp) {

    char *newEnv[] = { "PS=byj>", "WINDOW=1", NULL };
    int pid = fork();
    if ( pid == 0 ) {
        execve( "./printEnv", argv, newEnv);
    } else {
        int returnStatus;    

        waitpid(pid, &returnStatus, 0); 
        printf("\n\n");
        execvp( "./printEnv", argv);
    }

}
