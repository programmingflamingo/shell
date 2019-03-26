#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>

struct rusage usage;
int signalCaughtsegv      = 0;

int signalCaughtint       = 0;
int signalCaughttstp      = 0;

int signalCaughtalrm      = 0;

int signalCaughtusr1      = 0;
int signalCaughtusr1count = 0;
int signalCaughtusr2      = 0;

int x = 3;
int child;

int doubleArraySize(char *array[], int arraySizeOG) {
  int i;
  char *temp[arraySizeOG*2];

  for(i=0; i<arraySizeOG; i++)
    temp[i] = array[i];
    
  array = temp;
        
  return arraySizeOG * 2;
}

void segv_handler( int sig ) {
        signalCaughtsegv = sig;
        usage.ru_nsignals++;
	return;
}

void int_handler( int sig ) {
        signalCaughtint = sig;
        usage.ru_nsignals++;
	return;
}

void tstp_handler( int sig ) {
        signalCaughttstp = sig;
        usage.ru_nsignals++;
        signalCaughttstp = 0;
	return;
}

void alrm_handler( int sig ) {
        signalCaughtalrm = sig;
        usage.ru_nsignals++;
    return;
}

void usr1_handler( int sig ) {
        signalCaughtusr1 = sig;
        signalCaughtusr1count++;
        usage.ru_nsignals++;

        if(signalCaughtusr1count==x)
          kill (child, SIGUSR2);
    return;
}

void usr2_handler( int sig ) {
        signalCaughtusr2 = sig;
        usage.ru_nsignals++;
    return;
}

int main( int argc, char ** argv )
{
  printf("CS 361 HW #2\n");
  printf("Name : Michael Slomczynski\n");
  printf("UIN  : 660304702\n");
  printf("NetID: ms11\n");
  
  if(argc > 1)
    x = atoi(argv[1]);

  size_t linesize = 500;
  char *line;

  int i = 0, size = 50;
  char **args;
  char *tkn;

  args = (char **) malloc (size * sizeof(char *));
  if(args == NULL) {
    perror("3) Error Malloc");
    exit(EXIT_FAILURE);
  }
  
  /**************************************************
  |Beginning of Shell                               |
  **************************************************/  
  write(1, "\nShell Begin", 12);
  do { 
    line = (char*)malloc(linesize*sizeof(char));
    if(line == NULL) {
      perror("1) Error Malloc");
      exit(EXIT_FAILURE);
    }
    
    i = 0;

    write(1, "\nInput Command: ", 16);
    getline(&line, &linesize, stdin);
    line[strcspn(line, "\r\n")] = '\0';
    
    /**************************************************
    |Step 1: Tokenize Inputs                          |
    **************************************************/ 
    tkn = strtok(line, " ");
    while(tkn != NULL) {
    
      args[i] = (char*)malloc((strlen(tkn)+1)*sizeof(char));
      if(args[i] == NULL) {
        perror("2) Error Malloc");
        exit(EXIT_FAILURE);
      }

      args[i] = tkn;
      //printf(" args[%d] = %s\n", i, args[i]);

      tkn = strtok(NULL, " ");
      i++;
      
      if(i>=size)
        size = doubleArraySize(args, size);
    }
    if(line[0]!='\0')
      args[i] = NULL;
    else
    {
      args[0] = "\n";
      args[1] = NULL;
    }
    /**************************************************
    |Step 2: Fork, Exec, and Wait                     |
    **************************************************/ 
    pid_t pid = fork();
    signal( SIGSEGV, segv_handler );
    signal( SIGINT,  int_handler  );
    signal( SIGTSTP, tstp_handler );
    signal( SIGALRM, alrm_handler );
    signal( SIGUSR1, usr1_handler );
    signal( SIGUSR2, usr2_handler );
    /**************************************************
    |2.a: Fork Failed                                 |
    **************************************************/ 
    if (pid == -1) {
      perror("Error Fork");
      exit(EXIT_FAILURE);
    }

    /**************************************************
    |2.b: Child Process                               |
    **************************************************/ 
    if (pid == 0) {
      printf("   Child(%d) |PPID(%d) cPID(%d) \n", getpid(), getppid(), pid);
      
      execvp(args[0], args);
      perror("      Error Exec"); 
      _exit(EXIT_FAILURE);
    }

    /**************************************************
    |2.c: Parent Process                              |
    **************************************************/ 
    if (pid > 0) {
      printf("Parent(%d)   |PPID(%d) cPID(%d) \n", getpid(), getppid(), pid);

      child = pid;

      int status;
      (void)wait4(pid, &status, 0, &usage);
    
      if(WIFSIGNALED( status ))
        printf("Child (%d) Termination Signal: %d\n", pid, WTERMSIG(status));

      if (WIFEXITED( status ))
        printf("Child (%d) Exit Value %d\n", pid, WEXITSTATUS(status));

      printf("Child (%d) Number of Page Faults: %ld\n", pid, usage.ru_minflt+usage.ru_majflt);

      printf("Child (%d) Number of Signals: %ld (unreliable)\n", pid, usage.ru_nsignals);
      
      signalCaughtusr1count = 0;
    }
  }while(strcmp(line, "exit"));
  
  /**************************************************
  |End of Shell                                     |
  **************************************************/  
  printf("Shell End\n");

  return 0;
}

