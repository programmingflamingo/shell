CC = gcc
CFLAGS = -Wall -g

all: ss mc

ss: ss4 #ss1 ss2 ss3 

mc: mc4 #mc1 mc2 mc3

#simpleShell
#ss1: 
#	$(CC) $(CFLAGS) -E simpleShell.c -o ss.i
#ss2:
#	$(CC) $(CFLAGS) -S simpleShell.c -o ss.s
#ss3:
#	$(CC) $(CFLAGS) -c simpleShell.c -o ss.o
ss4:
	$(CC) $(CFLAGS) simpleShell.c -o ss

#monteCarlo
#mc1: 
#	$(CC) $(CFLAGS) -E monteCarlo.c -o mc.i
#mc2:
#	$(CC) $(CFLAGS) -S monteCarlo.c -o mc.s
#mc3:
#	$(CC) $(CFLAGS) -c monteCarlo.c -o mc.o
mc4:
	$(CC) $(CFLAGS) monteCarlo.c -o mc

clean:
	rm -f *ss.i *ss.s *ss.o *ss *mc.i *mc.s *mc.o *mc

cleanss:
	rm -f *ss.i *ss.s *ss.o *ss

cleanmc:
	rm -f *mc.i *mc.s *mc.o *mc

runss:
	./ss

runmc:
	./mc
