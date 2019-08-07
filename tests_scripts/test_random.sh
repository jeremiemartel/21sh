# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_random.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/08/07 15:57:50 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Shell"
	launch "Random"
	test_launch 'mkdir test123 ; cd test123 ; ls -a ; ls | cat | wc -c > fifi ; cat fifi ; cd .. ; rm -r test123'
	test_launch '.' './'
	test_launch '..' '../'
	test_launch '././..' '../../.'
	test_launch 'echo tamer > file' 'echo okalm >> file' '<file cat' '<file cat >file' 'cat file' 'rm file'
	test_launch 'env -i TERM=$TERM PATH=/bin ./21sh' 'cd includes ; pwd ; cd - ; pwd'

	launch "segfault"
	if [ ! -e ".segfault" ] ; then
		echo -e ${red}"Can't find .segfault executable"${eoc}
	else
		test_launch './.segfault'
		test_launch './.segfault | wc'
		test_launch 'ls | ./.segfault'
		test_launch './.segfault && echo $?'
		test_launch './.segfault || echo $?'
		test_launch './.segfault ; echo $?'
		test_launch './.segfault | wc && echo $?'
		test_launch 'ls | ./.segfault && echo $?'
	fi
finish
