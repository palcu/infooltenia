#!/bin/bash
# compile script; don't change unless you know what you're doing!
# asserts:
#	pwd	==> eval/
#	$1	==> student ID
#	$2	==> problem name
# does not recompile if nothing changed
# TODO: external modules not yet implemented

BASE="stud/$1/$2"

if [ ! -d $BASE.tmp ]; then
	mkdir $BASE.tmp
fi

if [ -e $BASE.c ]; then
	EXT=.c
	CMD=gcc
elif [ -e $BASE.cpp ]; then
	EXT=.cpp
	CMD=g++
elif [ -e $BASE.pas ]; then
	if REMAKE $BASE.tmp/compile $BASE.pas ; then
		echo -n ' comp'
		rm -f $BASE.tmp/the.exe
		ln $BASE.pas work
		cd work
		
		# Edit here to change Free Pascal options
		# Do NOT remove -Xs !!!
		fpc -Xs $2.pas >/dev/null
		cd ..
		if [ -x work/$2 ]; then
			mv work/$2 $BASE.tmp/the.exe
		fi
		rm -f work/* $BASE.tmp/compile
		touch $BASE.tmp/compile
	fi
	exit 0
else
	echo "No source file! ($2.c, $2.cpp or $2.pas)" >.tmp
	if [ -e $BASE.tmp/compile ] && cmp -s .tmp $BASE.tmp/compile ; then
		rm .tmp
	else
		mv .tmp $BASE.tmp/compile
	fi
	exit 0
fi

# gets here for gcc or g++
if REMAKE $BASE.tmp/compile $BASE$EXT ; then 
	echo -n ' comp'
	rm -f $BASE.tmp/the.exe
	$CMD -O2 -static -o$BASE.tmp/the.exe $BASE$EXT -lm >$BASE.tmp/compile 2>&1
fi
exit 0
