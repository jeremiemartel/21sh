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

path=".."
exec="21sh"

verbose=""

if [ -n $1 ] ; then
	verbose="ok"
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

source functions.sh

for file in `ls test_*` ; do
	source $file
done

## Other tests
launch "Others"
	test 'mkdir test123 ; cd test123 ; ls -a ; ls | cat | wc -c > fifi ; cat fifi ; cd .. ; rm -r test123'
finish

rm ${exec}
