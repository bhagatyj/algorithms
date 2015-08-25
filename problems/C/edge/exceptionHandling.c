// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

/*
 * Buffer to save the environment (exection context)
 * of the process
 */
sigjmp_buf jmpbuf;

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
   // process on receipt of a specific signal
   mySigAction.sa_handler = handler;
   sigaction(SIGFPE, &mySigAction, NULL);

   for (i = -5; i <= 5; i++) { 
      // Invoke sigsetjmp to save the execution context 
      // (environment) into the jmpbuf, so that we can 
      // return to this place at a later time.
      // Non-zero 2nd argument implies that current signal
      // mask will also be saved.
      ret = sigsetjmp(jmpbuf, 1);
      if ( ret == 0) { 
         printf("inverse of %d is %f\n", i, inverse(i) );
      } else {
         printf("Encountered SIGFPE during the function\n");
      }
   }
    return 0;
}
