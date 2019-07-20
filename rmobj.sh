#!/bin/bash
inf=500
a=1
b=".git"
strindex() { 
  x="${1%%$2*}"
  [[ $x = $1 ]] && return -1 || return ${#x}
}
Delete_object(){
	if [ "$1" == "$b" ]
	then
		return
	fi
	let a=a+1
	if [ "$a" -gt "$inf" ]
	then
		return
	fi
	find $1  ! -name "*.cpp" ! -name "*.sh"  ! -name "*.pdf" ! -name "*.txt" ! -perm -444 -type f  -exec rm {} \;
	for file in $1
	do
        if test -d $file 
		then
			Delete_object $file
		fi
	done
}
Delete_object ./