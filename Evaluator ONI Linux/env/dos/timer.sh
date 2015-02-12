#!/bin/bash

echo "FIXME: call sematics changed"
exit 1

# timer script
# asserts:
#	pwd	==> eval/
#	$1	==> name of exe, relative from eval/
# output goes to eval/rumstat.tmp
# TODO: maybe run programs as unpriviledged user

if [ -z "$1" -o ! -z "$2" ]; then
	echo "FATAL ERROR: invalid call to timer.sh" >&2
	exit 1
fi

cd work
export THE_EXE="`cygpath -w -a ../$1`"

if ! ../env/dos/dotime.sh 0.500 ; then
	exit 1
fi

if [ -e killed.tmp ]; then
	echo "hardkill >$LIM_TIME 0 Timeout! (program crashes DOS environment)" >../runstat.tmp
else
	mv runstat.tmp ..
fi

rm -f runstat.tmp killed.tmp
exit 0
