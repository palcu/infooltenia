/* --- To be compiled with Borland C

This is a DOS program, that runs the contestant's program and times it.
It can do more accurate timing than a Cygwin program, and can usually kill
a program exceeding the timelimit, using DOS functions (and thus avoiding
a "hard-kill").

Normal operation:
0. redirect stdout and stderr to ./stdout
1. call 'sendsig 1'
2. run the contestant's program, and kill it if it exceeds the time
3. write runtmp.tmp and rename it to runstat.tmp (rename is atomic)
4. if waitnkill is not ready to kill ntvdm (killed.tmp does not exist),
call 'sendsig 2'

In case of errors, tries to write runstat.tmp with FATAL ERROR message
and call 'sendsig t'.
*/
#pragma option -r- -N- -O1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <io.h>
#include <sys\stat.h>

#include <dos.h>
#include <process.h>
#include <float.h>
#include <conio.h>

#define SIG_EXE		"..\\env\\dos\\sendsig.exe"
#define OUT_FILE	"runstat.tmp"
#define TMP_FILE	"runtmp.tmp"
#define KILL_FILE	"killed.tmp"

#define INTR	0x1C	/* The clock tick interrupt */

// #define TIME	(*(long far volatile *) 0x046Cl)

unsigned _stklen = 0x1000;
unsigned _heaplen = 0x3000;

int timelim;
volatile int elapsed;
void interrupt (*ohandler)(void);
char far volatile *p_indos;

void interrupt handler(void)
{
	ohandler();
	if((++elapsed >= timelim) && !(*p_indos)) {
		asm {
			sti
			mov ax,0x4C00
			int 0x21
		}
	}
}

int main(int argc /*, char **argv */)
{
	int stat, saverr, fd;
	char *env_exe = getenv("THE_EXE");
	FILE *f;

	if((argc != 1) || !getenv("LIM_TIME") || !env_exe || !getenv("WNKPID")) {
		fputs(	"usage: runit\n"
			"environment:\n"
			"   LIM_TIME - time limit in seconds (real number)\n"
			"   THE_EXE  - executable file to run\n"
			"   WNKPID   - pid of waitnkill process\n", stderr);

		f = fopen(OUT_FILE, "w");
		fputs("FATAL -.--- ?? FATAL ERROR: invalid call to runit\n", f);
		fclose(f);

		spawnl(P_WAIT, SIG_EXE, SIG_EXE, "t", NULL);
		return(1);
	}

	timelim = (int) ceil(atof(getenv("LIM_TIME")) / 0.055);

	// get address of p_indos flag
	asm {
		mov  ah,0x34
		int  0x21
	}
	((unsigned *) &p_indos)[1] = _ES;
	((unsigned *) &p_indos)[0] = _BX;

	if(((fd = creat("stdout", S_IREAD | S_IWRITE)) == -1)
	  || (dup2(fd, 1) == -1) || (dup2(fd, 2) == -1) || (close(fd) == -1)) {
		char *s = strerror(errno);

		fprintf(stderr, "./stdout: %s\n", s);

		f = fopen(OUT_FILE, "w");
		fprintf(f, "FATAL -.--- ?? FATAL ERROR: ./stdout: %s\n", s);
		fclose(f);

		spawnl(P_WAIT, SIG_EXE, SIG_EXE, "t", NULL);
		return(1);
	}

	if(spawnl(P_WAIT, SIG_EXE, SIG_EXE, "1", NULL)) {
		int e = errno;

		perror("FATAL ERROR IN EVALUATOR\n" SIG_EXE);
		fprintf(fopen(OUT_FILE, "w"),
			"FATAL -.--- ?? FATAL ERROR: " SIG_EXE ": %s\n",
			strerror(e));
		return(1);
	}

	_fpreset();
	ohandler = getvect(INTR);
	setvect(INTR, handler);

//	stat = spawnl(P_WAIT, env_exe, "the.exe", NULL);
	stat = system(env_exe);

	saverr = errno;
	setvect(INTR, ohandler);
	_fpreset();

	if(!(f = fopen(TMP_FILE, "w")))
		goto out_err;
	if(stat == -1)
		fprintf(f, "badexec -.--- 0 spawn: %s\n", strerror(saverr));
	else if(elapsed >= timelim) {
		fprintf(f, "timeout %.3f 0 Time limit exceeded!\n",
			elapsed / 18.2);
	} else if(stat) {
		fprintf(f, "badstat %.3f 0 Nonzero exit status: %d\n",
			elapsed / 18.2, stat);
	} else fprintf(f, "runok %.3f -- output needs to be verified\n",
			elapsed / 18.2);
	if(ferror(f) || fclose(f)) {
out_err:
		perror("FATAL ERROR IN EVALUATOR!\n" TMP_FILE);
		if(access(KILL_FILE, 0))
			spawnl(P_WAIT, SIG_EXE, SIG_EXE, "t", NULL);
		exit(1);
	}

	/* synchronization code */
	if(rename(TMP_FILE, OUT_FILE))
		goto out_err;
	if(access(KILL_FILE, 0)
	  && spawnl(P_WAIT, SIG_EXE, SIG_EXE, "2", NULL)) {
		perror("FATAL ERROR IN EVALUATOR!\n" SIG_EXE);
		exit(1);
	}
	exit(0);
	return(1);	/* shouldn't happen */
}
