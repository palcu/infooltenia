#!/bin/bash
# timer script
# asserts:
#	pwd	==> eval/
#	$1	==> problem type (normal / interact)
#	$2	==> name of exe, relative from eval/
#	$3	==> (optional) name of interactive module
# output goes to eval/runstat.tmp

sync

if [ "$1" != normal -a "$1" != interact ] || [ -z "$2" -o ! -z "$4" ]; then
	echo "FATAL ERROR: invalid call to timer.sh" >&2
	exit 1
fi

ln $2 work

if [ $1 != interact ]; then
	cd work
	exec ../env/linux/runit the.exe nobody $LIM_TIME \
		$LIM_DATA $LIM_STACK /dev/null "" 0 >../runstat.tmp
fi

ln $3 work-int
cd work-int
mknod pipe-in.tmp p
mknod pipe-out.tmp p

# some sanity restrictions for the interactive system
../env/linux/runit interact nobody 20.0 32.0 32.0 \
	pipe-out.tmp pipe-in.tmp 0 >intstat.tmp &
INT_PID=$!

cd ../work
../env/linux/runit the.exe nobody $LIM_TIME $LIM_DATA $LIM_STACK \
	../work-int/pipe-in.tmp ../work-int/pipe-out.tmp 1 >../runstat.tmp 
#EXE_PID=$!
STAT=$?
if [ $STAT -ne 0 ]; then
	exit $STAT
fi

wait $INT_PID
STAT=$?
#THEEXE="`ps aux | grep runit | awk ' {print $2}'`"
#ps aux | grep the.exe >&2
#echo "$EXE_PID-$THEEXE-" 1>&2
#if [ ! -z "$THEEXE" ]; then
#	kill $THEXE
#fi

if [ $STAT -ne 0 ]; then
	exit $STAT
fi

cd ../work-int
read STAT JUNK <intstat.tmp
if [ "$STAT" != runok ]; then
	echo "FATAL ERROR in env/linux/timer.sh: interact did not terminate successfully" >&2
	cat intstat.tmp >&2
	exit 1
fi

rm intstat.tmp pipe-in.tmp pipe-out.tmp
