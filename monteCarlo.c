#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include <limits.h>

#define LIMIT ULLONG_MAX

/**************************************************
|1.a Globals                                      |
**************************************************/  
unsigned long int countSegFault = 0;
unsigned long int countEvlAttmp = 0;

unsigned long int report = 10;

static jmp_buf bufferA;

int signalCaughtsegv = 0;

int signalCaughtint  = 0;
int signalCaughttstp = 0;

int signalCaughtalrm = 0;

int signalCaughtusr1 = 0;
int signalCaughtusr2 = 0;

void segv_handler( int sig ) {
        signalCaughtsegv = sig;
        
        if(countEvlAttmp%report==0) {
            kill (getppid(), SIGUSR1);
            report=report*10;
        }

        countEvlAttmp++;
        countSegFault++;
        
        if(countEvlAttmp<LIMIT)
          signalCaughtsegv = 0;
        
        else {
          /**************************************************
          |4.a Exiting from SEGV                            |
          **************************************************/  
            
          printf("SEGV");
          printf("\n NUM Seg Faults  : %lu\n", countSegFault);    //number of seg faults
          printf(" NUM Evaluations : %lu\n", countEvlAttmp);      //number of evaluations attempted
 
          long double ratio = 0.0;

          if(countSegFault>0)
            ratio =  (countSegFault*100.0) / (countEvlAttmp*1.0);  
        
          if(report%1000000000000000000==0)
            printf(" SEGV to EVAL    : %.18Lf\n", ratio);
          else if(report%100000000000000000==0)
            printf(" SEGV to EVAL    : %.17Lf\n", ratio);
          else if(report%10000000000000000==0)
            printf(" SEGV to EVAL    : %.16Lf\n", ratio);
          else if(report%1000000000000000==0)
            printf(" SEGV to EVAL    : %.15Lf\n", ratio);
          else if(report%100000000000000==0)
            printf(" SEGV to EVAL    : %.14Lf\n", ratio);
          else if(report%10000000000000==0)
            printf(" SEGV to EVAL    : %.13Lf\n", ratio);
          else if(report%1000000000000==0)
            printf(" SEGV to EVAL    : %.12Lf\n", ratio);
          else if(report%100000000000==0)
            printf(" SEGV to EVAL    : %.11Lf\n", ratio);
          else if(report%10000000000==0)
            printf(" SEGV to EVAL    : %.10Lf\n", ratio);
          else if(report%1000000000==0)
            printf(" SEGV to EVAL    : %.9Lf\n", ratio);        
          else if(report%100000000==0)
            printf(" SEGV to EVAL    : %.8Lf\n", ratio);
          else if(report%10000000==0)
            printf(" SEGV to EVAL    : %.7Lf\n", ratio);
          else if(report%1000000==0)
            printf(" SEGV to EVAL    : %.6Lf\n", ratio);
          else if(report%100000==0)
            printf(" SEGV to EVAL    : %.5Lf\n", ratio);
          else if(report%10000==0)
           printf(" SEGV to EVAL    : %.4Lf\n", ratio);
          else if(report%1000==0)
            printf(" SEGV to EVAL    : %.3Lf\n", ratio);
        
          exit ((int) ratio);
        }
        return;
}

void int_handler( int sig ) {
        signalCaughtint = sig;

        /**************************************************
        |4.b Exiting from INT                            |
        **************************************************/  
        
        printf("\n NUM Seg Faults  : %lu\n", countSegFault);    //number of seg faults
        printf(" NUM Evaluations : %lu\n", countEvlAttmp);      //number of evaluations attempted

        long double ratio = 0.0;

        if(countSegFault>0)
          ratio =  (countSegFault*100.0) / (countEvlAttmp*1.0);  

        if(report%1000000000000000000==0)
          printf(" SEGV to EVAL    : %.18Lf\n", ratio);
        else if(report%100000000000000000==0)
          printf(" SEGV to EVAL    : %.17Lf\n", ratio);
        else if(report%10000000000000000==0)
          printf(" SEGV to EVAL    : %.16Lf\n", ratio);
        else if(report%1000000000000000==0)
          printf(" SEGV to EVAL    : %.15Lf\n", ratio);
        else if(report%100000000000000==0)
          printf(" SEGV to EVAL    : %.14Lf\n", ratio);
        else if(report%10000000000000==0)
          printf(" SEGV to EVAL    : %.13Lf\n", ratio);
        else if(report%1000000000000==0)
          printf(" SEGV to EVAL    : %.12Lf\n", ratio);
        else if(report%100000000000==0)
          printf(" SEGV to EVAL    : %.11Lf\n", ratio);
        else if(report%10000000000==0)
          printf(" SEGV to EVAL    : %.10Lf\n", ratio);
        else if(report%1000000000==0)
          printf(" SEGV to EVAL    : %.9Lf\n", ratio);        
        else if(report%100000000==0)
          printf(" SEGV to EVAL    : %.8Lf\n", ratio);
        else if(report%10000000==0)
          printf(" SEGV to EVAL    : %.7Lf\n", ratio);
        else if(report%1000000==0)
          printf(" SEGV to EVAL    : %.6Lf\n", ratio);
        else if(report%100000==0)
          printf(" SEGV to EVAL    : %.5Lf\n", ratio);
        else if(report%10000==0)
          printf(" SEGV to EVAL    : %.4Lf\n", ratio);
        else if(report%1000==0)
          printf(" SEGV to EVAL    : %.3Lf\n", ratio);
        
        exit ((int) ratio);
	return;
}

void tstp_handler( int sig ) {
        signalCaughttstp = sig;
        
        printf("\n NUM Seg Faults  : %lu\n", countSegFault);    //number of seg faults
        printf(" NUM Evaluations : %lu\n", countEvlAttmp);      //number of evaluations attempted

        long double ratio = 0.0;

        if(countSegFault>0)
          ratio =  (countSegFault*100.0) / (countEvlAttmp*1.0);  

        if(report%1000000000000000000==0)
          printf(" SEGV to EVAL    : %.18Lf\n", ratio);
        else if(report%100000000000000000==0)
          printf(" SEGV to EVAL    : %.17Lf\n", ratio);
        else if(report%10000000000000000==0)
          printf(" SEGV to EVAL    : %.16Lf\n", ratio);
        else if(report%1000000000000000==0)
          printf(" SEGV to EVAL    : %.15Lf\n", ratio);
        else if(report%100000000000000==0)
          printf(" SEGV to EVAL    : %.14Lf\n", ratio);
        else if(report%10000000000000==0)
          printf(" SEGV to EVAL    : %.13Lf\n", ratio);
        else if(report%1000000000000==0)
          printf(" SEGV to EVAL    : %.12Lf\n", ratio);
        else if(report%100000000000==0)
          printf(" SEGV to EVAL    : %.11Lf\n", ratio);
        else if(report%10000000000==0)
          printf(" SEGV to EVAL    : %.10Lf\n", ratio);
        else if(report%1000000000==0)
          printf(" SEGV to EVAL    : %.9Lf\n", ratio);        
        else if(report%100000000==0)
          printf(" SEGV to EVAL    : %.8Lf\n", ratio);
        else if(report%10000000==0)
          printf(" SEGV to EVAL    : %.7Lf\n", ratio);
        else if(report%1000000==0)
          printf(" SEGV to EVAL    : %.6Lf\n", ratio);
        else if(report%100000==0)
          printf(" SEGV to EVAL    : %.5Lf\n", ratio);
        else if(report%10000==0)
          printf(" SEGV to EVAL    : %.4Lf\n", ratio);
        else if(report%1000==0)
          printf(" SEGV to EVAL    : %.3Lf\n", ratio);
        
        signalCaughttstp = 0;
	return;
}

void alrm_handler( int sig ) {
        signalCaughtalrm = sig;
        
        /**************************************************
        |4.c Exiting from ALRM                            |
        **************************************************/  
        
        printf("ALRM");
        printf("\n NUM Seg Faults  : %lu\n", countSegFault);    //number of seg faults
        printf(" NUM Evaluations : %lu\n", countEvlAttmp);      //number of evaluations attempted
        
        long double ratio = 0.0;

        if(countSegFault>0)
          ratio =  (countSegFault*100.0) / (countEvlAttmp*1.0);  

        if(report%1000000000000000000==0)
          printf(" SEGV to EVAL    : %.18Lf\n", ratio);
        else if(report%100000000000000000==0)
          printf(" SEGV to EVAL    : %.17Lf\n", ratio);
        else if(report%10000000000000000==0)
          printf(" SEGV to EVAL    : %.16Lf\n", ratio);
        else if(report%1000000000000000==0)
          printf(" SEGV to EVAL    : %.15Lf\n", ratio);
        else if(report%100000000000000==0)
          printf(" SEGV to EVAL    : %.14Lf\n", ratio);
        else if(report%10000000000000==0)
          printf(" SEGV to EVAL    : %.13Lf\n", ratio);
        else if(report%1000000000000==0)
          printf(" SEGV to EVAL    : %.12Lf\n", ratio);
        else if(report%100000000000==0)
          printf(" SEGV to EVAL    : %.11Lf\n", ratio);
        else if(report%10000000000==0)
          printf(" SEGV to EVAL    : %.10Lf\n", ratio);
        else if(report%1000000000==0)
          printf(" SEGV to EVAL    : %.9Lf\n", ratio);        
        else if(report%100000000==0)
          printf(" SEGV to EVAL    : %.8Lf\n", ratio);
        else if(report%10000000==0)
          printf(" SEGV to EVAL    : %.7Lf\n", ratio);
        else if(report%1000000==0)
          printf(" SEGV to EVAL    : %.6Lf\n", ratio);
        else if(report%100000==0)
          printf(" SEGV to EVAL    : %.5Lf\n", ratio);
        else if(report%10000==0)
          printf(" SEGV to EVAL    : %.4Lf\n", ratio);
        else if(report%1000==0)
          printf(" SEGV to EVAL    : %.3Lf\n", ratio);
        
        exit ((int) ratio);
	return;
}

void usr1_handler( int sig ) {
        signalCaughtusr1 = sig;
	return;
}

void usr2_handler( int sig ) {
        signalCaughtusr2 = sig;
        
        /**************************************************
        |4.d Exiting from USR2                            |
        **************************************************/  
        
        printf("USR2");
        printf("\n NUM Seg Faults  : %lu\n", countSegFault);    //number of seg faults
        printf(" NUM Evaluations : %lu\n", countEvlAttmp);      //number of evaluations attempted

        long double ratio = 0.0;

        if(countSegFault>0)
          ratio =  (countSegFault*100.0) / (countEvlAttmp*1.0);  

        if(report%1000000000000000000==0)
          printf(" SEGV to EVAL    : %.18Lf\n", ratio);
        else if(report%100000000000000000==0)
          printf(" SEGV to EVAL    : %.17Lf\n", ratio);
        else if(report%10000000000000000==0)
          printf(" SEGV to EVAL    : %.16Lf\n", ratio);
        else if(report%1000000000000000==0)
          printf(" SEGV to EVAL    : %.15Lf\n", ratio);
        else if(report%100000000000000==0)
          printf(" SEGV to EVAL    : %.14Lf\n", ratio);
        else if(report%10000000000000==0)
          printf(" SEGV to EVAL    : %.13Lf\n", ratio);
        else if(report%1000000000000==0)
          printf(" SEGV to EVAL    : %.12Lf\n", ratio);
        else if(report%100000000000==0)
          printf(" SEGV to EVAL    : %.11Lf\n", ratio);
        else if(report%10000000000==0)
          printf(" SEGV to EVAL    : %.10Lf\n", ratio);
        else if(report%1000000000==0)
          printf(" SEGV to EVAL    : %.9Lf\n", ratio);        
        else if(report%100000000==0)
          printf(" SEGV to EVAL    : %.8Lf\n", ratio);
        else if(report%10000000==0)
          printf(" SEGV to EVAL    : %.7Lf\n", ratio);
        else if(report%1000000==0)
          printf(" SEGV to EVAL    : %.6Lf\n", ratio);
        else if(report%100000==0)
          printf(" SEGV to EVAL    : %.5Lf\n", ratio);
        else if(report%10000==0)
          printf(" SEGV to EVAL    : %.4Lf\n", ratio);
        else if(report%1000==0)
          printf(" SEGV to EVAL    : %.3Lf\n", ratio);

        exit ((int) ratio);
	return;
}

int main( int argc, char ** argv )
{
  /**************************************************
  |1.b srand and Parse Command Arguments            |
  **************************************************/  

  srand(time(NULL));
  double x = -1.0;
  if(argc > 1)
    x = atof(argv[1]);

  unsigned int b = 0;
  if(x>=0.0)
    b = (unsigned int) x;  

  
  /**************************************************
  |2 Signal Handlers                                |
  **************************************************/  

  signal( SIGSEGV, segv_handler );
  signal( SIGINT,  int_handler  );
  signal( SIGTSTP, tstp_handler );
  signal( SIGALRM, alrm_handler );
  signal( SIGUSR1, usr1_handler );
  signal( SIGUSR2, usr2_handler );

  alarm(b);
  
  for(; countEvlAttmp<LIMIT; countEvlAttmp++) {
      
      /**************************************************
      |3.a sigsetjmp                                    |
      **************************************************/  
      sigsetjmp(bufferA, 0);
      
      /**************************************************
      |3.b Calling rand() and storing in an (int *)     |
      **************************************************/  
      int *rp;
      rp = (int *) rand();

      /**************************************************
      |3.c Copying the (int *) to an (int)              |
      **************************************************/  
      int r = *rp;

      free(rp);
      rp = NULL;
      
      if( signalCaughtsegv ) 
          siglongjmp(bufferA, 1);    
  }
  //Should not get here
  return 0;
}

