// Getting the pid of parent in the child
// proc_t p_info;
// get_proc_stats(pid_num, &p_info);
// int parent_pid = p_info.ppid;

#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <sys/time.h>
#include <sched.h>
#include <sys/types.h>
#include <signal.h>
#include <semaphore.h>

typedef unsigned int u32;
typedef unsigned long long u64;

#define SEM_NAME "/mySemaphore"

void
syserr(char *s)
{
   printf("Exit \n ");
   perror(s);
   exit(1);
}

sem_t *sem = NULL;

void init ( void ) {
   int fd;
   sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, 0);
   // sem_open creates a file in /dev/shm
   printf("Sem is %p\n", sem);
}

int main(int ac, char *av[])
{
   pid_t pid; 
   int ret;

   init();
   if ( (pid = fork() ) < 0 ) {
      syserr("Forking failed\n");
   } else if (pid == 0 ) {
      // Child process
      sigset_t waitset;
      int sig, ret;

      sleep(3);
      printf("Child: Let me print first\n");
      sem_post(sem);
      sigemptyset( &waitset );
      sigaddset( &waitset, SIGUSR1);
      ret = sigwait( &waitset, &sig); 
      if (ret == 0) {
          printf("sigwait returned sig %d\n", sig);
          if (sig == SIGUSR1) {
              printf("Child: Thanks...\n");
          }
      } else {
          printf("sigwait returned %d\n", ret);
      }
   } else {
      sem_wait(sem);
      printf("Parent: Ok I will wait \n");
      // Unlink marks the file in /dev/shm/ for removal after all processes
      // close it. It can be called by this process - even before closing the
      // file descriptor.
      sleep(3);
      kill(pid, SIGUSR1);
      ret = sem_unlink(SEM_NAME);
      printf("Ret code of unlink is %d\n", ret);
   }
   sem_close(sem);
}

