# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/07/05 11:29:15 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
	test_launch "mkdir dir ; cd dir ; rm -r ../dir ; pwd" "cd .. ; pwd"

launch "hash"
	test_launch "hash"
	test_launch "hash qkjhbdnsj"
	test_launch "hash -e"
	test_launch "hash -r" "hash"
	test_launch "cat file " "hash -r" "hash"

launch "cd"
	test_launch "cd" "pwd"
	test_launch "cd ~/" "pwd" "cd .. ; pwd"
	test_launch "cd /" "cd ../.." "pwd"
	test_launch "cd ." "pwd" "cd ../../" "pwd"
	test_launch "cd ../../../../../../../../../../"
	test_launch "cd -P /var" "pwd"
	test_launch "cd -L /var" "pwd"
	test_launch "mkdir sandbox ; cd sandbox ; ln -s ../sandbox  ./link" "cd ./link" "ls -la" "pwd" "cd .." "rm -r sandbox"
	test_launch "mkdir dir ; ln -s dir link" "cd dir ; pwd ; pwd -P" "cd ../link ; pwd ; pwd -P" "cd -P ../link ; pwd ; pwd -P" "cd .. ; rm -r dir link"

	test_launch "cd -" "pwd"
	test_launch "cd ../../ ; cd -"
	test_launch "PWD=asdqw OLDPWD=Okalm cd -" "cd -"
	test_launch "PWD=asdqw OLDPWD=Okalm" "cd -"
	test_launch "touch file" "cd file && wd && cd .." "rm file"
	test_launch "mkdir dir ; chmod 100 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 600 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 666 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"
	test_launch "mkdir dir ; chmod 667 dir ; cd dir && pwd && cd .. ; chmod 777 dir ; rm -r dir" "rm -rf dir"

launch "exit"
	test_launch 'exit ; ls'
	test_launch 'exit' 'ls'
	test_launch 'exit && ls'
	test_launch 'exit && ls ; ls'
	test_launch 'exit || ls'
	test_launch 'exit 1 ; echo $?'
	test_launch 'exit 12 ; echo $?'
	test_launch 'exit 1231983287123 ; echo $?'
	test_launch 'echo tamer ; exit 3 ; echo $?'
	test_launch 'exit 123 ; echo $?'

launch "setenv"
	# test_given_res 'okalm=sd' '' 'setenv okalm=sd' 'env | grep okalm'
	# test_given_res "" "21sh: '=asd' bad assignment" 'setenv =asd'
	# test_given_res "" "21sh: '=' bad assignment" 'setenv =' 'env | grep =asd'

launch "unsetenv"
	# test_launch 'unsetenv PATH'
	# test_launch 'unsetenv'
	# test_launch 'unsetenv -wasd qwe -APSD asd #@'
	# test_launch 'unsetenv PWD OLDPWD ; env grep PWD'
	# test_launch 'unsetenv PWD A OLD PWD' 'env | grep PWD'
	# test_launch 'unsetenv PATH ; echo lol ; brew'

launch "env"
	test_launch 'env | grep HOME'
	test_launch 'env | grep USER'
	test_launch 'env | grep jkas'
	test_launch 'env -i brew'
	test_launch 'echo "#!/bin/bash" > file' 'echo "echo Hello World" >> file ; chmod +x file ; env ./file' 'rm file'
	test_launch 'echo "#!/bin/bash" > file' 'echo "echo Hello World" >> file ; chmod +x file ; env -i ./file' 'rm file'
	test_launch 'env -i rora=okalm'
	test_launch 'env -i pasd=laisjd pqwei=asdasd asdasd=scvsd'
	test_launch 'env -i'
	test_launch 'env -asd'
	test_launch 'env -asd ls'
	test_launch 'env -i asdq= brew'
	test_launch 'env -i =aasd'
	test_launch 'env -i =aasd ls'
	test_launch 'env -i ='
	test_launch 'env -i = ls'
	test_launch 'env -i var=asd q=qwe e=ewer r=asd t=asda y=asd u= i= o= p=sf a=asd s=asd d=asd f=asd g=hgfd h=sdf j=fsa env'
	test_launch 'env -i var=asd q=qwe e=ewer r=asd t=asda y=asd u= i= o= p=sf a=asd s=asd d=asd f=asd g=hgfd h=sdf j=fsa env'

#	launch "Deprecated"
	# test_launch "PWD=" "OLDPWD=" "cd -" "cd -"
	# test_launch "PWD=/ OLDPWD=/var cd - ; cd -"
	# test_launch "PWD=/ OLDPWD=/var cd -" "cd -"
	# test_launch "ln -s . link" "cd link ; pwd" "cd link ; pwd" "pwd -P" " pwd -L" "rm link"
	# test_launch "ln -s . link" "cd link" "cd link" "pwd -L ; pwd -P" "rm link" # "cd .." "pwd ; cd ."

finish
