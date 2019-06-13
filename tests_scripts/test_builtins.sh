# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_builtins.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/06/10 12:41:28 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##	Builtin tests
##		Echo :
launch "Echo (builtin)"
	test "echo -n okalm"
	test "echo -n "
	test "echo"
	test "echo okalm"
	test 'echo $env'
	test 'echo $TERM'
	test 'echo $poasd'
	test 'echo $TERM $PATH'
	test 'echo -n $TERM $PATH'
	test 'echo $var $var $var'
	test 'echo $s#var $var'

launch "pwd (builtin)"
	test "pwd"
	test "pwd | cat -e"
	test "pwd | cat -e | wc"
	test "PWD=" "OLDPWD=" "pwd"

launch "hash (builtin)"
	test "hash"
	test "hash -r" "hash"
	test "cat file " "hash -r" "hash"


launch "cd (builtin)"
	test "cd" "pwd"
	test "cd ~/" "pwd" "cd .. ; pwd"
	test "cd /" "cd ../.." "pwd"
	test "cd ." "pwd" "cd ../../" "pwd"

launch "set (builtin)"
	test "set"

finish
