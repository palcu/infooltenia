# FILE: params.sh
# PURPOSE: define problem parameters
# careful! no spaces around equals signs
# all variables must be set (if one is N/A, set it to an empty string)

# file lists may contain any number of files, separated by spaces
# input files
IFILES="poligon.in"

# expected output files
OFILES="poligon.out"

# files used by the verifier
KFILES="poligon.ok"

# time limit in seconds
LIM_TIME="0.400"

# settings that are only honored under Linux
if [ "$ENV" == linux ]; then
	# data segment limit (in Mb, real number)
	LIM_DATA="2.0"

	# stack segment limit (in Mb, real number)
	LIM_STACK="2.0"
fi

# modules don't work under Linux yet
if [ "$ENV" == dos ]; then
	# name of module or empty string
	MODULE=""
fi
