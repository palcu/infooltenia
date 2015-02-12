/* --- to be compiled with gcc under cygwin environment

Runs in background while the contestants program is running in a
Virtual DOS Machine.

Normal operation:
1.  sends SIGINT to dotime.sh when it's ready to wait to go to step 2
2.  waits for SIGUSR1 (sent by sendsig), which signals that runit is ready 
to execute the contestant's program.
3.  waits for some time (more than the normal time limit). If it receives
SIGUSR2 (signalling runit is about to exit), it simply returns.
4.  otherwise, calls kill.sh to terminate the ntvdm process (a "hard kill").
This is needed because programs can easily crash the DOS timer. 

The command line arguments are:
$1 <time1>	--> the normal time limit
$2 <time2>	--> the "extra" time limit before doing a hard kill
$3 <notifpid>	--> pid to signal when ready to start (usually the shell)
$4 <cmd>	--> the hard-kill command (usually kill.sh)
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#define RET_OKAY	19

jmp_buf jb;

void sighand(int sig)
{
	if(sig == SIGUSR2)
		exit(RET_OKAY);
	longjmp(jb, 1);
}

int main(int argc, char **argv)
{
	volatile double t;
	struct timeval tv;
	
	if(argc != 5) {
		fputs("usage: waitnkill <time1> <time2> <notifpid> <cmd>\n", stderr);
		return(1);
	}
	t = atof(argv[1]) + atof(argv[2]);
	
	signal(SIGUSR1, sighand);
	signal(SIGUSR2, sighand);
	
	if(!setjmp(jb)) {	/* wait for SIGUSR1 */
		kill(atoi(argv[3]), SIGINT);
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		select(0, NULL, NULL, NULL, &tv);
		signal(SIGUSR1, SIG_IGN);
		fputs("FATAL ERROR: waitnkill tired of waiting for SIGUSR1\n", stderr);
		return(1);
	}
		
	/* wait for SIGUSR2 */
	signal(SIGUSR1, SIG_IGN);
	tv.tv_sec = (int) t;
	tv.tv_usec = (int) ((t - (int) t) * 1e6);
	select(0, NULL, NULL, NULL, &tv);
	signal(SIGUSR2, SIG_IGN);
	
	if(creat("killed.tmp", 0644) == -1) {
		perror("creat(\"killed.tmp\")");
		return(1);
	}
	if(!access("runstat.tmp", 0))
		return(RET_OKAY);
	printf("[ hard kill ");
	fflush(stdout);
	execl(argv[4], argv[4], NULL);
	perror(argv[4]);
	return(1);
}
