/* --- to be compiled with gcc under the cygwin environment 
this is called by runit (a DOS program), in two circumstances:
1. just before the contestant's program is executed, to deliver SIGUSR1
2. after the contestant's program has been safely terminated --> SIGUSR2

these two signals are sent to waitnkill (pid is in WNKPID environment variable)
this program might also be called to deliver SIGTERM to waitnkill, if a
fatal error occurs in runit (this will stop the evaluation).
*/
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t pid;
	char *s;

	if(argc != 2) {
		fputs("***** usage: sendsig <1|2|t>\n", stderr);
		return(1);
	}
	if(!(s = getenv("WNKPID")) || !(pid = atoi(s))) {
		fputs("***** sendsig: missing WNKPID\n", stderr);
		return(1);
	}
	{char sx[1024];sprintf(sx,"ps -W >>/eval/pids.tmp/%d", pid);
	system(sx);
	}
	if(*argv[1] == '1')
		kill(pid, SIGUSR1);
	else if(access("killed.tmp", 0))
		kill(pid, (*argv[1] == 't') ? SIGTERM : SIGUSR2);
	return(0);
}
