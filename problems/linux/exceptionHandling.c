#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

typedef struct {
    struct timeval time;
    uint64_t tick;
             char place[256];
} time_keeper_t;

enum {
    TK_START,
    TK_post_sigaction,
    TK_MAX
} tk_enum_types;

#define TK_STR(x) #x

time_keeper_t tk[TK_MAX] = { 
   { {0, 0}, 0, TK_STR(TK_START) },
   { {0, 0}, 0, TK_STR(TK_post_sigaction) } };


void
print_tk( void )
{

   int i;
   for ( i=0; i< TK_MAX; i++) {
      if (i == 0) {
         printf("time: %d %d : %llu : %s\n", (int) tk[i].time.tv_sec,
                  (int) tk[i].time.tv_usec, tk[i].tick, tk[i].place );
      } else {                     
         int dusec, dsec;          
         uint64_t dtick;
         if (tk[i].time.tv_sec == tk[i-1].time.tv_sec) {
            dsec = 0;
            dusec = (int) (tk[i].time.tv_usec - tk[i-1].time.tv_usec) ;
         } else {
            dusec = (1000000 - tk[i-1].time.tv_usec) + tk[i].time.tv_usec;
            dsec = 0;
         }
         dtick = tk[i].tick - tk[i-1].tick;
         printf(
            "time: %d %d : tick: %llu delta usec %d %d : delta tick %llu : %s\n",
            (int) tk[i].time.tv_sec, (int) tk[i].time.tv_usec, tk[i].tick,
            dsec, dusec, dtick, tk[i].place );
      }
   }
   fflush(stdout);
}



/*
 * Buffer to save the environment (exection context)
 * of the process
 */
sigjmp_buf jmpbuf;

uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

/*
 * This handler will be invoked if there is an exception.
 * It needs to call longjmp to return to pre-exception
 * location: the location at which sigsetjmp was invoked
 * and provide the value that needs to be returned to the
 * call of sigjmp.
 */
void handler(int sig)
{
   // longjmp restores the environment saved by the most 
   // recent invocation of sigsetjmp() in the same thread
   longjmp(jmpbuf, 1);
}

float inverse(int x)
{
   // Note:
   // 1.0/x returns proper value for all values of x
   // For the case of 0, it returns infinity.
   // 1/x causes the exception if x is 0.
    return (1.0/x + 1/x);
}

int main(void)
{
   int i, ret;
   struct sigaction mySigAction;

   // sigaction() system call is used to change the action taken by a
   // process on receipt of a specific signal.
   // We use it for handling SIGFPE. The handler returns 1,
   // thereby printing an Encountered SIGFPE message and continuing
   // with the loop.
   gettimeofday( &(tk[TK_START].time), NULL );
   tk[TK_START].tick = rdtsc();
   mySigAction.sa_handler = handler;
   sigaction(SIGFPE, &mySigAction, NULL);
   gettimeofday( &(tk[TK_post_sigaction].time), NULL );
   tk[TK_post_sigaction].tick = rdtsc();

   for (i = -5; i <= 5; i++) { 
      // Invoke sigsetjmp to save the execution context 
      // (environment) into the jmpbuf, so that we can 
      // return to this place at a later time.
      // Non-zero 2nd argument implies that current signal
      // mask will also be saved.
      ret = sigsetjmp(jmpbuf, 1);
      if ( ret == 0) { 
         printf("inverse of %d is %f\n", i, inverse(i) );
        ;
      } else {
         printf("Encountered SIGFPE during the function\n");
        ;
      }
   }
   // Profiling to find out how long it took to save the env
   // and setup the handler.
   print_tk();
   return 0;
}
