#!/bin/bash
# installation script for Cygwin environment

if [ "$OS" != "Windows_NT" ]; then
	echo "can only run under Cygwin/Win2000 !!!"
	exit 1
fi

if [ -z "$CYGROOT" ]; then
	echo "add CYGROOT system variable and run me again !!!"
	exit 1
fi

if [ "`cygpath -u $CYGROOT`" != / ]; then
	echo "they CYGROOT variable seems invalid..."
	echo "it should be: `cygpath -w /`"
	exit 1
fi

if [ ! -d /eval/inst ]; then
	echo "seems I'm not installed in /eval/inst !!!"
	exit 1
fi

if [ -e /cygwin.bat ]; then
	echo "modifying start-up procedure; use 'Start cygwin' from now on!"
	cp "/eval/inst/Start cygwin.lnk" /
	cp "/eval/inst/Start cygwin.lnk" "`cygpath -u -D`"
	mv /cygwin.bat "/cygwin.bat -- not used"
fi

echo "installation successful (I hope)... good luck!"
