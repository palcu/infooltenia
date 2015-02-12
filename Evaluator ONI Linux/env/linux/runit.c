#include <asm/param.h>
//#include <asm/page.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <math.h>

const char usage[] =
	"usage: runit <exe> <user> <time> <data> <stack> <stdin> <stdout> <rev>\n"
	"  <exe>     The executable file (must be in working directory)\n"
	"  <user>    Run program as this unprivileged user\n"
	"  <time>    Running time limit (in seconds, real number)\n"
	"  <data>    Limit on data segment (in Mb, real number)\n"
	"  <stack>   Limit on stack segment (in Mb, real number)\n"
	"  <stdin>   Program's standard input (usually /dev/null)\n"
	"  <stdout>  Program's standard output (null if work/stdout)\n"
	"  <rev>     Reverse order in which stdin/stdout are opened (0/1)\n";

int time_lim_us;		/* in usecs */
pid_t child_pid;	/* child process process id */
int memory = 0;		/* memory used, maximum value, in kb */
unsigned long time = 0;	/* time used, maximum value */

// every 0.1 seconds
#define alarm_period_us 100000
int alarm_count = 0;

/* read the user time from /proc/pid/stat */
void read_time()
{
	char nbuf[1024];
	char buf[1024];
	unsigned long local_time;
	unsigned long vsize;
	int ti;
	long int tld;
	unsigned long tu;
	char ts[1024];
	char tc;
	int fd;

	sprintf(nbuf, "/proc/%d/stat", child_pid);
	fd = open(nbuf, O_RDONLY);
	if (fd == -1) 
	{
		fprintf(stderr, "Could not read %s\n", nbuf);
		return;
	}

	buf[0] = 0;
	read(fd, buf, sizeof(buf));

        // see man proc
	sscanf(buf, "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %d %ld %lu %lu", 
               &ti, // pid
               ts, // command
	       &tc, // state
	       &ti, // ppid
	       &ti, // pgrg
	       &ti, // session
	       &ti, // tty
	       &ti, // tpgid
	       &tu, // flags
	       &tu, // minflt
	       &tu, // cminflt
	       &tu, // majflt
	       &tu, // cmajflt
	       &local_time, // utime
	       &tu, // stime
	       &tld, // cutime
	       &tld, // cstime
	       &tld, // priority
	       &tld, // nice
	       &ti, // 0
	       &tld, // itrealvalue
	       &tu, // starttime
	       &vsize // vsize (bytes)
	       );
	local_time *= 1000 * (1000 / HZ); /* microseconds */
	if (local_time > time)
		time = local_time;

        vsize /= 1024; // in kb
	if (vsize > memory)
		memory = vsize;
	//fprintf(stderr,"\n%d %ld\n",memory,time);
}

/* handler from SIG_ALRM */
void sig_alrm(int signo)
{
	struct itimerval tv;

	read_time();
	
	if (time > time_lim_us)
	{
		kill(child_pid, SIGKILL);
		printf("tle %d.%03d %d 0 Time limit exceeded!\n", 
		       (time_lim_us + 1) / 1000000, ((time_lim_us) % 1000000)/1000 +1, memory); //normal
		exit(0);
	}

	alarm_count++;
  if (alarm_count > 3 * time_lim_us / alarm_period_us)
	{
		kill(child_pid, SIGKILL);
		printf("tle %d.%03d %d 0 Time limit exceeded!\n", 
		       (time_lim_us + 1) / 1000000, ((time_lim_us) % 1000000)/1000 +1, memory); //sleep
		exit(0);
	}

	tv.it_interval.tv_sec = tv.it_interval.tv_usec = 0;
	tv.it_value.tv_sec = alarm_period_us / 1000000;
	tv.it_value.tv_usec = alarm_period_us % 1000000;
	setitimer(ITIMER_REAL, &tv, NULL);
}

/* in case something wrong happens */
void perr(const char *s)
{
	char *se = strerror(errno);
	
	write(2, s, strlen(s));
	write(2, ": ", 2);
	write(2, se, strlen(se));
	write(2, "\n", 1);
	exit(-1);
}

int main(int argc, char **argv)
{
	int data_lim, stk_lim, rev;
	struct passwd *p;
	
	if (argc != 9) /* exactly 8 parameters */
	{
		fputs(usage, stderr);
		return 1;
	}

	if (geteuid()) 
	{
		fputs("runit: must be run as root (or suid root)\n", stderr);
		return 1;
	}

	if(!(p = getpwnam(argv[2]))) 
	{
		fprintf(stderr, "%s: no such user\n", argv[2]);
		return(1);
	}

	time_lim_us = (int) ceil(1000000 * atof(argv[3]));
	data_lim = (int) ceil(1024 * 1024 * atof(argv[4]));
	stk_lim = (int) ceil(1024 * 1024 * atof(argv[5])); 

	rev = atoi(argv[8]);
	
	signal(SIGALRM, sig_alrm);
	
	switch(child_pid = fork()) 
	{
		case -1:
			perror("fork(2)");
			return 1;
		
		default: /* the initial process */
		{
			//usleep(3);
			//read_time();
			struct itimerval tv;
			struct rusage usage;
			int stat, runtime;

			tv.it_interval.tv_sec = tv.it_interval.tv_usec = 0;
			tv.it_value.tv_sec = alarm_period_us / 1000000;
			tv.it_value.tv_usec = alarm_period_us % 1000000;
			setitimer(ITIMER_REAL, &tv, NULL);
		
			waitpid(child_pid, &stat, 0); /* wait the child process */
			signal(SIGALRM, SIG_IGN);

			getrusage(RUSAGE_CHILDREN, &usage);

                        // runtime is in milliseconds
			runtime = usage.ru_utime.tv_sec * 1000 + usage.ru_utime.tv_usec / 1000;
			if (runtime > time_lim_us / 1000)
			{
				printf("timelimit %d.%03d %d 0 Time limit exceeded!\n", 
				       (time_lim_us+1) / 1000000, ((time_lim_us) % 1000000)/1000 +1 , memory); //normal
				return 0;
			}
		
			if (WIFEXITED(stat)) 
			{
				if(!WEXITSTATUS(stat))
					printf("runok %d.%03d %d -- output needs to be verified\n", 
					       runtime / 1000, runtime % 1000, memory);
				else
					printf("badexit %d.%03d %d 0 Nonzero exit status: %d\n", 
					       runtime / 1000, runtime % 1000,  memory, WEXITSTATUS(stat));
			} else 
				if (WIFSIGNALED(stat)) {
					int signal = WTERMSIG(stat);

					if (signal == 9)
						printf("memlimit %d.%03d %d 0 Memory exceeded\n", 
						       runtime / 1000, runtime % 1000, memory);
					else
						printf("signal %d.%03d %d 0 Killed by signal: %d\n", 
						       runtime / 1000, runtime % 1000, memory, signal);
				}
				else 
					abort();
			return 0;
		}
		
		/* child process */
		case 0: {
			struct rlimit rl;
			int fd, i;
			sigset_t sigs;

			/* limitations */
			rl.rlim_cur = 2;
			rl.rlim_max = 2;

			setrlimit(RLIMIT_NPROC, &rl); // de ce 2 procese ???
			rl.rlim_cur = data_lim;
			rl.rlim_max = data_lim;
			if(setrlimit(RLIMIT_AS, &rl))
			  fprintf(stderr, "Limit AS error ");

      rl.rlim_cur = stk_lim;
			rl.rlim_max = stk_lim;
			if(setrlimit(RLIMIT_STACK, &rl))
			  fprintf(stderr,"Limit STACK error ");
      
      rl.rlim_cur = data_lim;
			rl.rlim_max = data_lim;
			if(setrlimit(RLIMIT_DATA, &rl))
			  fprintf(stderr,"Limit DATA error ");
      
      rl.rlim_cur = data_lim;
			rl.rlim_max = data_lim;
			if(setrlimit(RLIMIT_MEMLOCK, &rl))
			  fprintf(stderr,"Limit MEMLOCK error ");
      
			sigemptyset(&sigs);
			sigaddset(&sigs, SIGPIPE);
			sigprocmask(SIG_BLOCK, &sigs, NULL);

			for(i = 0; i < 2; i++) {
				if (i ^ rev) 
				{
					if ((fd = open(argv[6], O_RDONLY)) == -1)
						perr("open(1)");
					dup2(fd, 0);
					close(fd);
				} else 
				if (*argv[7]) 
				{
					if ((fd = open(argv[7], O_WRONLY)) == -1)
						perr("open(2)");
					dup2(fd, 1);
					close(fd);
				}
			}
		
			if (chroot("."))
				perr("chroot(2)");
			if (setgid(p->pw_gid) || setgroups(0, NULL))
				perr("setgid(2)");
			usleep(100);
			if (setuid(p->pw_uid))
				perr("setuid(2)");
			
			if ((fd = creat("stdout", 0644)) == -1)
				perr("creat(2)");
			dup2(fd, 2);
			if (!*argv[7])
				dup2(fd, 1);
			close(fd);
		
			/* the actual program execution */
			execl(argv[1], argv[1], NULL);
			perr(argv[1]);
			return -1;
		}
	}
}

