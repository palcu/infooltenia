#!/bin/bash
# called by waitnkill after the grace period has expired
# kills the Virtual DOS Machine
# can't distinguish between several ntvdm's, so there must be only one running
while ps -sW | grep -i 'system32\\ntvdm.exe' >kill.tmp ; do
	if [ `wc -l <kill.tmp` -ne 1 ]; then
		echo "FATAL ERROR: unexpected ntvdm processes" >&2
		exit 1
	fi
	read WINPID REST <kill.tmp
	/bin/kill -f $WINPID
	echo -n "."
	
	# nice way to do a delay, under these circumstances :^)
	nice -n+1 true
done
rm kill.tmp
echo -n " dead ]"

exit 19	
# special return code convention: 19 signifies success
