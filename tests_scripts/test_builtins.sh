# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/06/25 11:32:29 by jmartel          ###   ########.fr        #
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
	test_launch "mkdir sandbox ; cd sandbox ; ln -s ../sandbox  ./link" "cd ./link" "ls -la" "pwd" "cd .." "rm -r sandbox"
	test_launch "mkdir dir ; ln -s dir link" "cd dir" "pwd" "cd ../link ; ls" "rm -r dir ; rm file ; rm link"

launch "env"
	test_launch 'env'
	test_launch 'env -i ls'
	test_launch 'env -i path=/bin ls'
	test_launch 'env -i PATH=/bin ls'
	test_launch 'echo "echo Hello World" > file ; chmod +x file ; ./file' 'rm file'
	test_launch 'echo "echo Hello World" > file ; chmod +x file ; env -i ./file' 'rm file'
	test_launch 'env -i rora=okalm'
	test_launch 'env pasd=laisjd pqwei=asdasd asdasd=scvsd'
	test_launch 'env -i'
	test_launch 'env -asd'
	test_launch 'env -asd ls'
	test_launch 'env asdq='
	test_launch 'env asdq= ls'
	test_launch 'env =aasd'
	test_launch 'env =aasd ls'
	test_launch 'env ='
	test_launch 'env = ls'

finish
