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
##	./launcher [-v] [-q] [-2] [file]
##		-v : Activate Valgrind tests
##		-2 : Activate comparison on stderr
##		-q : Activate quiet mode : only show OK or KO
##		file : give the name of a file, or simply it's kind
##			(ex : expansions for test_expansions.sh)
##			else, every files would be launched

path="../../"
suppressions_file="my_supp.supp"
exec="21sh"
log_dir="logs" # watchout we rm -rf this


test_stderr=0
verbose="ok"
for arg in $@ ; do
	if [ "$arg" = "-v" ] ; then
		valgrind=true
		rm -rf "${log_dir}" 
		mkdir -p $log_dir
	fi

	if [ "$arg" = "-2" ] ; then
		test_stderr=1
	fi

	if [ "$arg" = "-q" ] ; then
		verbose=""
	fi

	if [ -f "test_${arg}.sh" ] ; then
		file="test_${arg}.sh"
	elif [ -f "${arg}" ] ; then
		file=${arg}
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

make -C $path debug && cp ${path}/${exec} .

((passed=0))
((tried=0))
((diff_passed=0))
((diff_tried=0))

source functions.sh

if [ -n "$file" ] ; then
	source $file
else
	for file in `ls test_*` ; do
		source $file
	done
fi


## Other tests
launch "Others"
	test 'mkdir test123 ; cd test123 ; ls -a ; ls | cat | wc -c > fifi ; cat fifi ; cd .. ; rm -r test123'
finish

rm ${exec}
echo "passed ${passed} valgrind tests out of ${tried}"
echo "passed ${diff_passed} diff tests out of ${diff_tried}"
rm -rf "${exec}.dSYM"
