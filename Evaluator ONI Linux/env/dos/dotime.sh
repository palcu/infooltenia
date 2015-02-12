#!/bin/bash
# driver that handles the actual running and timing of a program
# called by timer.sh and compile.sh (so that the compiler also runs
# in a secure environment)
# asserts:
#	pwd	 	==> /eval/work
#	$LIM_TIME	==> time limit
#	$THE_EXE	==> command line for DOS executable
#	$1		==> extra time before killing the DOS virtual machine
# generates killed.tmp (empty file) if the virtual machine was killed
# otherwise, non-empty runstat.tmp must exist

if [ -z "$LIM_TIME" -o -z "$THE_EXE" -o -z "$1" -o ! -z "$2" ]; then
	echo "FATAL ERROR: invalid call to dotime.sh" >&2
	exit 1
fi

rm -f runstat.tmp

if ps -sW | grep -i 'system32\\ntvdm.exe' ; then
	echo "FATAL ERROR: dos virtual machine running in background" >&2
	exit 1
fi

# waitnkill sends SIGINT to this shell ($$) to signal that it's ready
# we than launch the DOS program
DOSTART() {
	WNKPID=$! cygstart ../env/dos/Run-it.pif
}
trap DOSTART SIGINT

nice -n-1 ../env/dos/waitnkill $LIM_TIME $1 $$ ../env/dos/kill.sh &

while true; do
	wait $!
	RES=$?
	if [ $RES -lt 128 ]; then
		if [ $RES -eq 0 ]; then
			echo "FATAL ERROR: shoot! Cygwin bug..."
			exit 1
		fi
		if [ $RES -ne 19 ]; then
			echo "FATAL ERROR: error $RES in background waitnkill process" >&2
			exit 1
		fi
		break
	fi
done

# wait until the DOS virtual machine really terminates
for CNT in 7 6 5 4 3 2 1 0 ; do
	if ! ps -sW | grep -i -q 'system32\\ntvdm.exe' ; then
		break
	fi
	if [ $CNT -eq 0 ]; then
		echo "[ shoot! delayed hard-kill"
		touch killed.tmp
		../env/dos/kill.sh
	else
		nice -n+1 true
	fi
done

if [ -e killed.tmp -o ! -s runstat.tmp ]; then
	rm -f runstat.tmp
	touch killed.tmp
fi

exit 0
