#!/bin/bash
# The evaluation driver.
# Don't edit unless you really know what you're doing!


# Function also used by other scripts (which are called recursively)
# Called with a list of several files
# Checks if the first file is older than the other ones (and needs remaking)
REMAKE() {
	if [ -z "$1" ]; then
		echo "FATAL ERROR: invalid call to remake" >&2
		exit 1
	fi
	local FILE="$1"
	if [ ! -e "$1" ]; then
		return 0
	fi
	while [ ! -z "$2" ]; do
		if [ ! -e "$2" ]; then
			echo "FATAL ERROR: remake source missing: $2" >&2
			exit 1
		fi
		if [ "$2" -nt "$FILE" ]; then
			return 0
		fi
		shift
	done
	return 1
}
export -f REMAKE

# If circumstances require it, rerun a program for a particular test
# and/or regrade a program's output
# if the first argument in non-null, runs everything in "manual" mode
# (doesn't move files from work/ and doesn't update the official test results)
EVALTEST() {
	local TESTFILE=stud/$ID/$PROB.tmp/.tests/$TEST
	local STATUS=""
	local TMP=""
	local RUNTIME MEMORY MSG

	if [ ! -z "$IFILES$INT_IFILES" ]; then
		# list of dependencies for non-offline problems
		
		TMP="$(
			for FILE in $IFILES $INT_IFILES ; do
				echo prob/$PROB/$TEST-$FILE
			done
			if [ $PROB_TYPE == interact ]; then
				echo prob/$PROB/interact
			fi
		)"
	fi
		
	if [ $PROB_TYPE == offline ]; then
		#####
		# check if contestant's offline output files have changed
		#####
		RUNTIME="--"
		MEMORY="--"
		for FILE in $OFILES ; do
			if [ ! -r stud/$ID/$TEST-$FILE ]; then
				STATUS=missout
				MSG="0 Missing output file: $FILE"
			elif [ "$STATUS" != missout ] && REMAKE $TESTFILE stud/$ID/$TEST-$FILE ; then
				STATUS=runok
			fi
		done

		if [ "$STATUS" == missout -a -e $TESTFILE ] \
		   && ( echo "$STATUS $RUNTIME $MEMORY $MSG" | cmp -s $TESTFILE - ) ; then
		   	STATUS=""
		fi
		if [ ! -z "$STATUS" ]; then
			echo -n " $TEST"
		fi
	elif [ ! -z "$1" ] ||
	   REMAKE $TESTFILE stud/$ID/$PROB.tmp/compile $TMP prob/$PROB/params.sh ; then
		#####
		# (re)run student's program
		#####
		echo -n " $TEST"
		
		for FILE in $IFILES ; do
			cp prob/$PROB/$TEST-$FILE work/$FILE
			chmod a+r work/$FILE
		done
		if [ ! -z "$INT_IFILES" ]; then
			for FILE in $INT_IFILES ; do
				cp prob/$PROB/$TEST-$FILE work-int/$FILE
				chmod a+r work-int/$FILE
			done
		fi

		[ -z "$1" ] && rm -f stud/$ID/$PROB.tmp/$TEST-*
		
		if [ ! -x stud/$ID/$PROB.tmp/the.exe ]; then
			STATUS=noexec
			RUNTIME="--"
			MEMORY="--"
			MSG="0 Missing executable file"
			touch work/stdout
		else
			if [ -z "$1" ]; then
				rm -f stud/$ID/$PROB.tmp/$TEST-stdout
				touch stud/$ID/$PROB.tmp/$TEST-stdout
				echo "crash -.--- 0 Program crashes the grading machine" >$TESTFILE
			fi
			
			rm -f runstat.tmp
			if ! env/$ENV/timer.sh $PROB_TYPE \
			  stud/$ID/$PROB.tmp/the.exe prob/$PROB/interact ; then
				echo "ERROR IN env/$ENV/timer.sh" >&2
				exit 1
			fi
			read STATUS RUNTIME MEMORY MSG <runstat.tmp
			rm runstat.tmp
			
			[ -z "$1" ] && rm $TESTFILE
			
			if [ -z "$MSG" -o ! -r work/stdout ]; then
				echo "FATAL ERROR: invalid output from env/$ENV/timer.sh" >&2
				exit 1
			fi
			if [ $PROB_TYPE == interact -a $STATUS == runok -a -s work-int/stdout ]; then
				STATUS=badtalk
				MSG="0 $(<work-int/stdout)"			
			fi		
		fi

		if [ $PROB_TYPE == normal ]; then
			for FILE in stdout $OFILES ; do
				if [ -r work/$FILE ]; then
					[ -z "$1" ] &&
				   	mv work/$FILE stud/$ID/$PROB.tmp/$TEST-$FILE
				elif [ $STATUS == runok ]; then
					STATUS=missout
					MSG="0 Missing output file: $FILE"
				fi
			done
		fi

		if [ $PROB_TYPE == interact -a $STATUS == runok ]; then
                        for FILE in $INT_OFILES ; do
				if [ -r work-int/$FILE ]; then
					[ -z "$1" ] &&
					  mv work-int/$FILE stud/$ID/$PROB.tmp/$TEST-$FILE
				else
					echo "FATAL ERROR: missing output files from interact" >&2
					exit 1
				fi
			done
		fi
		
		[ -z "$1" ] && ( rm -rf work work-int ; mkdir work ; mkdir work-int ; chmod a+rwx work ; chmod a+rwx work-int ; )
	fi

	if [ -z "$STATUS" ]; then
		#####
		# check if output needs to be reverified
		#####
		TMP="$(
			for FILE in $KFILES ; do
				echo prob/$PROB/$TEST-$FILE
			done
		)"

		if REMAKE $TESTFILE $TMP prob/$PROB/.tests/$TEST prob/$PROB/verif ; then
			read STATUS RUNTIME MEMORY MSG <$TESTFILE
			if [ -z "$MSG" ]; then
				echo "FATAL ERROR: consistency check: $TESTFILE" >&2
				exit 1
			fi
			if [ "$STATUS" != runok ]; then
				touch $TESTFILE
				STATUS=""
			else
				echo -n " ~$TEST"
			fi
		fi
	fi
	if [ "$STATUS" == runok ]; then
		#####
		# verify output
		#####
		if [ $PROB_TYPE == offline ]; then
			for FILE in $OFILES ; do
				cp stud/$ID/$TEST-$FILE work/$FILE
			done
		elif [ -z "$1" ]; then
			for FILE in $OFILES $INT_OFILES ; do
				cp stud/$ID/$PROB.tmp/$TEST-$FILE work/$FILE
			done
		fi
		for FILE in $IFILES $INT_IFILES $KFILES ; do
			cp prob/$PROB/$TEST-$FILE work/$FILE
		done
		
		if [ $PROB_TYPE == interact  ]; then
			if [ -n "$OFILES" -a -e work-int/$OFILES ]; then
				mv work-int/$OFILES work/
			fi
			if [ -n "$INT_OFILES" -a -e work-int/$INT_OFILES ]; then
				mv work-int/$INT_OFILES work/
			fi
		fi

		MSG="$( cd work ; ../prob/$PROB/verif "$(<../prob/$PROB/.tests/$TEST)")"
		
		
		##echo " cd work ; ../prob/$PROB/verif "$(<../prob/$PROB/.tests/$TEST) >> /home/silviu/MSG
		if [ "$?" -ne 0 ]; then
			echo "FATAL ERROR: verifier returned non-zero error code" >&2
			exit 1
		fi
		[ -z "$1" ] && ( rm -rf work ; mkdir work ; chmod a+rwx work ; )
	fi
	if [ ! -z "$1" ]; then
		echo "$STATUS $RUNTIME $MEMORY $MSG" >work/test.res
	elif [ ! -z "$STATUS" ]; then
		echo "$STATUS $RUNTIME $MEMORY $MSG" >$TESTFILE
	fi
	return 0
}



# write res.txt for a problem; called in stud/$ID/$PROB.tmp/.tests
# writes to stdout (redirected to ../res.txt)
WRITERES() {
	local STATUS RUNTIME MEMORY SCORE MSG TOTAL
	
	echo "$HEADER"
	echo -e "$ID\t$EXTRA"
	echo
	echo "### Problem: $PROB"
	if [ -s ../compile ]; then
		echo 'Compiler output: <<<'
		cat ../compile
		echo '>>>'
		echo
	fi
	
	echo -e "Test\tScore\tTime\tMemory\tMessage"
	TOTAL=0
	for TEST in $ALLTESTS ; do
		read STATUS RUNTIME MEMORY SCORE MSG < $TEST
		if [ -z "$MSG" ]; then
			echo "FATAL ERROR: consistency check: .tests/$TEST" >&2
			exit 1
		fi
		echo -e "$TEST\t$SCORE\t$RUNTIME\t$MEMORY\t$MSG"
		TOTAL=$[$TOTAL + $SCORE]
	done
	echo -e "TOTAL\t$TOTAL\t--\t--"
}



# check availability of a certain file; report installation problem
CHKINST() {
	if [ ! $1 $2 ]; then
		echo "STARTUP PROBLEM: $2 (missing file or permissions: $1)" >&2
		exit 1
	fi
}



# evaluation code runs in a subshell; beeps come after this subshell exits
(
  
if [ -z "$2" -a ! -z "$1" -a -r $1-probs.txt ]; then
	ALL_PROBS=$(<$1-probs.txt)
elif [ -z "$5" -a ! -z "$4" -a "$1" == "--" ]; then
	ALL_PROBS=$2
	if [ ! -d stud/$3 ]; then
		echo "STARTUP PROBLEM: student $3 has no submissions directory" >&2
		exit 1
	fi
else
	cat >&2 <<-EOF
		STARTUP PROBLEM: usage:
		  $0 <day-to-evaluate>    -or-
		  $0 -- <problem> <contestant> <test>
		EOF
	exit 1
fi

if [ "$OS" == "Windows_NT" ]; then
	echo "Running under WinNT/cygwin"
	ENV=dos
elif [ "$OSTYPE" == "linux-gnu" ]; then
	echo "Running under Linux"
	ENV=linux
else
	echo "STARTUP PROBLEM: can't determine host environment" >&2
	exit 1
fi

if [ $ENV == dos ] && ps -sW | grep ntvdm ; then
	echo "STARTUP PROBLEM: Virtual Dos Machine running in background" >&2
	exit 1
fi

CHKINST -d env
CHKINST -x env/$ENV/timer.sh
CHKINST -x env/$ENV/compile.sh

CHKINST -r stud.txt
CHKINST -d stud
CHKINST -d prob
CHKINST -d work

rm -rf work
mkdir work
chmod a+rwx work
rm -rf work-int
mkdir work-int
chmod a+rwx work-int

  
for PROB in $ALL_PROBS ; do
	echo "******* Problem: $PROB"
	CHKINST -d prob/$PROB
	CHKINST -r prob/$PROB/params.sh
	CHKINST -r prob/$PROB/tests.txt
	CHKINST -x prob/$PROB/verif

	unset IFILES INT_IFILES OFILES INT_OFILES KFILES LIM_TIME LIM_DATA LIM_STACK PROB_TYPE LINK_IN
	. prob/$PROB/params.sh

	if [ "$PROB_TYPE" != interact -a ! -z "$INT_OFILES$INT_IFILES" ]; then
		echo 'STARTUP PROBLEM: cannot specify INT_* for non-interactive problems' >&2
		exit 1
	fi
	if [ -z "$OFILES$INT_OFILES" -o -z "$KFILES" ]; then
		echo 'STARTUP PROBLEM: missing variables in params.sh' >&2
		exit 1
	fi
	if [ -z "$PROB_TYPE" ]; then
		PROB_TYPE=normal
	fi
	if [ $PROB_TYPE == offline ]; then
		if [ ! -z "$IFILES" -o ! -z "$LIM_TIME" -o ! -z "$LIM_DATA" \
		     -o ! -z "$LIM_STACK" -o ! -z "$LINK_IN" ]; then
			echo 'STARTUP PROBLEM: invalid specification for off-line problem' >&2
			exit 1
		fi
	elif [ $PROB_TYPE == normal -o $PROB_TYPE == interact ]; then
		if [ -z "$IFILES$INT_IFILES" -o -z "$LIM_TIME" ]; then
			echo 'STARTUP PROBLEM: missing variables in params.sh' >&2
			exit 1
		fi
	else
		echo "STARTUP PROBLEM: unknown problem type" >&2
		exit 1
	fi
	export IFILES INT_IFILES OFILES INT_OFILES KFILES LIM_TIME PROB_TYPE LINK_IN
	
	if [ $ENV == dos ]; then
		if [ ! -z "$LIM_DATA" -o ! -z "$LIM_STACK" ]; then
			echo "WARNING: LIM_DATA and LIM_STACK not honored in Win/DOS environment" >&2
		fi
		if [ $PROB_TYPE == interact ]; then
			echo "STARTUP PROBLEM: problem type interact not support under DOS" >&2
			exit 1
		fi
		if [ ! -z "$LINK_IN" ]; then
			echo "FIXME: link-ins under DOS ...." >&2
			exit 1
#			CHKINST -r prob/$PROB/$LINK_IN.h
#			CHKINST -r prob/$PROB/$LINK_IN.obj
#			CHKINST -r prob/$PROB/$LINK_IN.tpu
		fi
	elif [ $ENV == linux ]; then
		if [ $PROB_TYPE != offline ] && [ -z "$LIM_DATA" -o -z "$LIM_STACK" ]; then
			echo 'WARNING: using defaults LIM_DATA=15.0, LIM_STACK=1.0' >&2
			LIM_DATA=15.0
			LIM_STACK=1.0
		fi
		export LIM_DATA LIM_STACK
		
		if [ $PROB_TYPE == interact ]; then
			CHKINST -x prob/$PROB/interact
		fi
		if [ ! -z "$LINK_IN" ]; then
			echo "STARTUP PROBLEM: link-ins not yet supported under Linux" >&2
			exit 1
		fi
	fi

	#####
	# Check for changes in tests.txt
	#####
	if [ ! -d prob/$PROB/.tests ]; then
		mkdir prob/$PROB/.tests
	fi
	(
		while read TEST EXTRA ; do
			if [ -z "$TEST" ]; then
				continue
			fi
			for FILE in $IFILES $INT_IFILES $KFILES ; do
				CHKINST -r prob/$PROB/$TEST-$FILE
			done
			
			echo $TEST
			if [ ! -e prob/$PROB/.tests/$TEST ] ||
			   [ "$(<prob/$PROB/.tests/$TEST)" != "$EXTRA" ]; then
				echo -n "$EXTRA" >prob/$PROB/.tests/$TEST
			fi
		done
	) <prob/$PROB/tests.txt >prob/$PROB/.tests/.tmp
	if [ "$?" -ne 0 ]; then
		exit 1
	fi
	if [ -e prob/$PROB/.tests/all ] && \
	   cmp -s prob/$PROB/.tests/.tmp prob/$PROB/.tests/all ; then
		rm prob/$PROB/.tests/.tmp
	else
		mv prob/$PROB/.tests/.tmp prob/$PROB/.tests/all
	fi
	ALLTESTS=$(<prob/$PROB/.tests/all)
	
	#####
	# Process every student (compile, evaluate, make res.txt for problem)
	#####
	if [ ! -z "$3" ]; then
		# manual override
		ID="$3"
		TEST="$4"
		if [ ! -r prob/$PROB/.tests/$TEST ]; then
			echo "STARTUP PROBLEM: no such test: $4" >&2
			exit 1
		fi
		EVALTEST justrun
	else
		(
			read HEADER
			CNT=0
			while read ID EXTRA ; do
				if [ -z "$ID" ]; then
					continue
				fi
				CNT=$[$CNT + 1]
				echo -n "[processed: $CNT of $PROB] $ID :"
			
				if [ ! -d stud/$ID ]; then
					mkdir stud/$ID
				fi
				if [ ! -d stud/$ID/$PROB.tmp ]; then
					mkdir stud/$ID/$PROB.tmp
				fi
				if [ ! -d stud/$ID/$PROB.tmp/.tests ]; then
					mkdir stud/$ID/$PROB.tmp/.tests
				fi

				if [ $PROB_TYPE == offline ]; then
					if [ ! -e stud/$ID/$PROB.tmp/compile ]; then
						touch stud/$ID/$PROB.tmp/compile
					fi
				elif ! env/$ENV/compile.sh $ID $PROB ; then
					echo "ERROR IN env/$ENV/compile.sh" >&2
					exit 1
				fi
			
				for TEST in $ALLTESTS ; do
					EVALTEST
				done
			
				cd stud/$ID/$PROB.tmp/.tests
				if REMAKE ../res.txt ../compile $ALLTESTS \
				     ../../../../prob/$PROB/.tests/all ; then
					WRITERES >../res.txt
				fi
				cd ../../../..
				echo
			done
		) <stud.txt
	fi
	if [ "$?" -ne 0 ]; then
		exit 1
	fi
done


# manual mode; no change in scores
if [ ! -z "$2" ]; then
	echo
	echo "Manual evaluation done. Outputs are in work/"
	echo "Official results and scores were NOT updated."
	exit 0
fi

#####
# Write allres.txt (general and for every student) and scores.txt
#####
echo "Writing results..."
echo -n -e "TOTAL\t" >scores.txt
ALL_RES="$(
	for PROB in $ALL_PROBS ; do
		echo "$PROB.tmp/res.txt"
		echo -e -n "$PROB\t" >>scores.txt
	done
)"
rm -f allres.txt
touch allres.txt

(
	read HEADER
	echo "$HEADER" >>scores.txt
	cd stud
	while read ID EXTRA ; do
		if [ -z "$ID" ]; then
			continue
		fi
		cd $ID
		
		#####
		# Update student's allres.txt if necessary
		#####
		if REMAKE allres.txt $ALL_RES ; then
			(
				echo "$HEADER"
				echo -e "$ID\t$EXTRA"
				echo
				echo "Results for: $1"
				
				TOTAL=0
				for FILE in $ALL_RES ; do
					tail -n+3 $FILE
					tail -n1 $FILE >.tmp
					read MAGIC SCORE REST <.tmp
					rm .tmp
					if [ "$MAGIC" != TOTAL ]; then
						echo "FATAL ERROR: consistency check: $FILE" >&2
						exit 1
					fi
					TOTAL=$[$TOTAL + $SCORE]
				done
				
				echo
				echo "--- TOTAL SCORE: $TOTAL"
				echo -e "\f"
			) >allres.txt
			if [ "$?" -ne 0 ]; then
				exit 1
			fi
			cat allres.txt >>../../allres.txt
		fi
		
		#####
		# Write entry in scores.txt
		#####
		TOTAL=0
		ALLSCORES=""
		for FILE in $ALL_RES ; do
			tail -n1 $FILE >.tmp
			read MAGIC SCORE REST <.tmp
			rm .tmp
			if [ "$MAGIC" != TOTAL ]; then
				echo "FATAL ERROR: consistency check: $FILE" >&2
				exit 1
			fi
			TOTAL=$[$TOTAL + $SCORE]
			ALLSCORES="$ALLSCORES\t$SCORE"
		done
		echo -e "$TOTAL$ALLSCORES\t$ID\t$EXTRA"
		cd ..
	done
	cd ..
) <stud.txt >>work/scores.txt
if [ "$?" -ne 0 ]; then
	exit 1
fi
sort -k1nr work/scores.txt >>scores.txt
rm work/scores.txt

echo DONE
)
if [ "$?" -ne 0 ]; then
	echo "ERRORS ENCOUNTERED; EVALUATION STOPPED" >&2
fi

# min 1sec delay necessary to ensure time stamps are correct (1sec precision)
if [ -z "$2" ]; then
	for i in 1 2 3 ; do
#		echo -e -n "\a"
		sleep 1
	done
fi
