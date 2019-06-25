#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    launcher.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:23 by jmartel           #+#    #+#              #
#    Updated: 2019/05/21 15:58:23 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Usage : 
##	./launcher [-v] [-q] [-2] [-e] [file]
##		-v : Activate Valgrind tests
##		-2 : Activate comparison on stderr
##		-q : Activate quiet mode : only show OK or KO
##		-e : Show only failed tests (hide [OK])
##		-r : Compare returned values with bash
##		file : give the name of a file, or simply it's kind
##			(ex : expansions for test_expansions.sh)
##			else, every files would be launched

path="../.."
suppressions_file="my_supp.supp"
exec="21sh"
log_dir="logs" # watchout we rm -rf this


test_stderr=""
verbose="ok"
show_error=""
test_returned_values=""
for arg in $@ ; do
	if [ "$arg" = "-v" ] ; then
		valgrind=true
		rm -rf "${log_dir}" 
		mkdir -p $log_dir
	fi

	if [ "$arg" = "-2" ] ; then
		test_stderr="ok"
	fi

	if [ "$arg" = "-q" ] ; then
		verbose=""
	fi

	if [ "$arg" = "-e" ] ; then
		show_error="ok"
	fi

	if [ "$arg" = "-r" ] ; then
		test_returned_values="ok"
	fi

	if [ -f "test_${arg}.sh" ] ; then
		file="$file test_${arg}.sh"
	elif [ -f "${arg}" ] ; then
		file="$fie ${arg}"
	fi
done

if [ ! -z $valgrind ] && [ ! -f $suppressions_file ] ; then
	echo "initializing the valgrind configuration..."
	./init.sh
	echo "OK !"
fi


#Colors
red=\\033[31m
green=\\033[32m
yellow=\\033[33m
blue=\\033[34m
pink=\\033[35m
cyan=\\033[36m
grey=\\033[37m
eoc=\\033[0m

make -C $path && cp ${path}/${exec} .

if ! [ -e "${path}/${exec}" ] ; then
	echo -e "${red}Can't find ${exec}${eoc}"
	exit 
fi

((passed=0))
((tried=0))
((diff_passed=0))
((diff_tried=0))

source functions.sh

if [ -n "$file" ] ; then
	for f in $file ; do
		source $f
	done
else
	for file in `ls test_*` ; do
		source $file
	done
fi

rm ${exec}
if [ "$tried" -ne 0 ] ; then
	echo "passed ${passed} valgrind tests out of ${tried}"
fi
echo "passed ${diff_passed} diff tests out of ${diff_tried}"

rm -rf "${exec}.dSYM"
