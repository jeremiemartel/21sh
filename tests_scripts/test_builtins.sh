# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 13:35:36 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##	Builtin tests
##		Echo :
launch "Builtins"
launch "Echo"
	test_launch "echo -n okalm"
	test_launch "echo -n "
	test_launch "echo"
	test_launch "echo okalm"
	test_launch 'echo $env'
	test_launch 'echo $TERM'
	test_launch 'echo $poasd'
	test_launch 'echo $TERM $PATH'
	test_launch 'echo -n $TERM $PATH'
	test_launch 'echo $var $var $var'
	test_launch 'echo $s#var $var'

launch "pwd"
	test_launch "pwd"
	test_launch "pwd | cat -e"
	test_launch "pwd | cat -e | wc"
	test_launch "PWD=" "OLDPWD=" "pwd"
	test_launch "pwd sqs"
	test_launch "pwd sqs aze"

launch "hash"
	test_launch "hash"
	test_launch "hash qkjhbdnsj"
	test_launch "hash -e"
	test_launch "hash -r" "hash"
	test_launch "cat file " "hash -r" "hash"
	test_launch "cat file" "hash" "hash"
	test_launch "ls" "pwd" "ls" "cat file" "hash" "hash -r" "hash"

launch "cd"
	test_launch "cd" "pwd"
	test_launch "cd ~/" "pwd" "cd .. ; pwd"
	test_launch "cd /" "cd ../.." "pwd"
	test_launch "cd ." "pwd" "cd ../../" "pwd"
	test_launch "cd ../../../../../../../../../../"
	test_launch "ln -s . ../link" "cd ../link" "ls" "pwd" "cd .." "rm link"
	test_launch "mkdir dir ; ln -s dir link" "cd dir" "pwd" "cd ../link ; ls" "rm -r dir ; rm file ; rm link"

finish
