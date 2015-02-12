#!/bin/bash
# script to make a machine more user friendly...
# designed especially to fix some ugliness in the default Cygwin installation

if [ ! -d /etc/profile.d ]; then
	echo "weird machine: no /etc/profile.d/; abandoning all hope..."
	exit 1
fi

if [ -e /etc/profile.d/beauty.sh ]; then
	echo "seems I already beautified this machine; quitting..."
	exit 1
fi

echo "writing /etc/profile.d/beauty.sh"

cat >/etc/profile.d/beauty.sh <<-"EOF"
	#!/bin/bash
	# added by /eval/inst/beautify.sh
	export PS1='\[\033]0;\w\007
	\033[32m\w\033[31;1m$\033[0m '

	TERM=vt100 dircolors /etc/dircolors -b >/tmp/dircolors.sh
	. /tmp/dircolors.sh
	rm /tmp/dircolors.sh
	alias d="ls -A -F --color=auto "

	export INPUTRC="/etc/inputrc"
	export LESS="-M -f -i -Q -S"
	export EDITOR="joe"
EOF


if [ ! -e /etc/dircolors ]; then
	echo "creating default /etc/dircolors"
	dircolors -p > /etc/dircolors
fi

if [ ! -e /etc/inputrc ]; then
	echo "creating /etc/inputrc"
	cat >/etc/inputrc <<-"EOF"
		set bell-style none
		set completion-ignore-case on
		set show-all-if-ambiguous on
		set visible-stats on
	EOF
fi
