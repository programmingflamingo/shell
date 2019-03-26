CS 361 HW #2
Michael Slomczynski
UIN  : 660304702
NetID: ms11

/**************************************************
|Issues with the Program                          |
**************************************************/  
The program should work as intended. The one issue that I am aware of with this program is with the ru_signals. I did try and implement it so it might give an answer other than zero. Other than that everything else should work.


/**************************************************
|How to Compile and Run                           |
**************************************************/  
You can COMPILE both monteCarlo.c and simpleShell.c with the command:
make
or individually:
make ss
make mc

After this if you want to RUN the simpleShell you can do so by typing:
./ss

Similarly to RUN monteCarlo you can type:
./mc

If you want to CLEAN the result of the compilation:
make clean
or individually:
make cleanss
make cleanmc

There are instructions to run the simpleShell and monteCarlo executables in the makefile. I wouldn't use them because you can't input any command line arguments. 
