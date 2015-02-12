#!/bin/bash
# compile script; don't change unless you know what you're doing!
# asserts:
#	pwd	==> eval/
#	$1	==> student ID
#	$2	==> problem name
# does not recompile if nothing changed

BASE="stud/$1/$2"

if [ ! -d $BASE.tmp ]; then
	mkdir $BASE.tmp
fi

unset EXT
if [ -e $BASE.c ]; then
	EXT=.c
	EXT2=.h
elif [ -e $BASE.cpp ]; then
	EXT=.cpp
	EXT2=.h
elif [ -e $BASE.pas ]; then
	EXT=.pas
	EXT2=.tpu
else
	echo "No source file! ($2.c, $2.cpp or $2.pas)" >.tmp
	if [ -e $BASE.tmp/compile ] && cmp -s .tmp $BASE.tmp/compile ; then
		rm .tmp
	else
		mv .tmp $BASE.tmp/compile
	fi
	exit 0
fi

unset MOD_FILE
if [ ! -z "$MODULE" ]; then
	MOD_FILE=prob/$PROB/$MODULE$EXT2
fi

if REMAKE $BASE.tmp/compile $BASE$EXT $MOD_FILE ; then
	echo -n ' comp'
	
	cp $BASE$EXT work
	cd work
	
	if [ $EXT == .pas ]; then
		if [ ! -z "$MODULE" ]; then
			cp ../$MOD_FILE .
		fi
		THE_EXE="tpc -Q"
	else
		THE_EXE="bcc $( (
				read
				read MAGIC OPTS
				if [ "$MAGIC" == "###" ]; then
					echo $OPTS
				fi
			) <$2$EXT )"
		if [ ! -z "$MODULE" ]; then
			THE_EXE="$THE_EXE -I`cygpath -a -w ../prob/$PROB`"
		fi
	fi
	export THE_EXE="$THE_EXE $2$EXT"
		
	# 10 sec time limit; extra time is negative, because we don't want
	# runit to try to kill bcc (which runs in protected mode)
	export LIM_TIME=15.000	
	if ! ../env/dos/dotime.sh -5.000 ; then
		exit 1
	fi
	
	if [ -e "killed.tmp" ]; then
		echo "WARNING: compiler timeout (most likely, compiler crash)" >&2
		cat >stdout <<-"EOF"
			--- Compiler took more than ten seconds to terminate.
			Most likely, the source file crashes the compiler.
			Contact the judges and have them look into this.
			EOF
		rm -f $2.exe
	fi
	mv stdout ../$BASE.tmp/compile
			
	cd ..
	if [ -e work/$2.exe ]; then
		mv work/$2.exe $BASE.tmp/the.exe
	else
		rm -f $BASE.tmp/the.exe
	fi
	rm -rf work/*
fi

exit 0
