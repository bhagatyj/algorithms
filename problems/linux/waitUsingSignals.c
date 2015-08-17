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
   struct sigaction action;

   init();

   // Install an action to ignore the signal SIGUSR1. 
   // We don't really want to handle the signal. Just
   // receiving the signal is information enough.
   action.sa_handler = SIG_IGN;
   sigaction(SIGUSR1, &action, NULL);

   if ( (pid = fork() ) < 0 ) {
      syserr("Forking failed\n");
   } else if (pid == 0 ) {
      // Child process
      sigset_t waitset;
      struct timespec delay;
      int ret;

      sleep(3);
      printf("Child: Let me print first\n");
      sem_post(sem);

	  // Now, it is my turn to go to sleep.
	  // Parent will let me know after it finishes
	  // its printing. 
	  sigprocmask( SIG_BLOCK, NULL, &waitset);
      sigaddset( &waitset, SIGUSR1);
      delay.tv_sec = 40;
      delay.tv_nsec = 10000;
	  sigprocmask( SIG_BLOCK, &waitset, NULL);
      ret = sigtimedwait( &waitset, NULL, &delay);
	  printf("Returned from timed wait\n");
      if (ret >= 0) {
          if ( ret == SIGUSR1) {
              printf("Child: Thanks...\n");
          }
      } else {
          printf("sigwait retcode %d \n", ret);
      }
	  // Sending the signal below would kill 
	  // if the dst process did not have a signal handler.
	  // But we have installed one.
      kill(pid, SIGUSR1);

   } else {
      sem_wait(sem);
      printf("Parent: Ok I will wait \n");
	  sleep(1);
      kill(pid, SIGUSR1);
      ret = sem_unlink(SEM_NAME);
      printf("Ret code of unlink is %d\n", ret);
	  sleep(10);
   }
   sem_close(sem);
}

