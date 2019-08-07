# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_pipes.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:47 by jmartel           #+#    #+#              #
#    Updated: 2019/08/07 15:29:56 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Pipes tests
launch "Pipes"
	launch "Simple"
		test_launch "ls | wc"
		test_launch "ls | wc | wc"
		test_launch "ls | wc | wc ; ls -a "
		test_launch "echo mdr | wc | cat -e | wc"

	launch "on Builtins"
		test_launch 'pwd' 'cd ../../.. | echo lol | exit | echo lol' 'pwd'
		test_launch 'exit | exit'
		test_launch 'exit | true | exit'
		test_launch 'yes | head -c1'
		test_launch 'cat | cat | wc'
		test_launch 'emacs | emacs'
		test_launch 'cat start.sh | wc | cat 1>&2 | ls | cat sd | ls'
		test_launch 'env ls | cat | wc'
		test_launch 'env echo tamre | wc'
		test_launch 'env cd .. ; exit | echo asd'

	launch "here documents"
		test_launch '<<eof cat' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '<<eof cat | wc' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '3<<eof cat' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '3<<eof cat | wc' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '1<<eof cat' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '1<<eof cat | wc' 'olqsd' 'qdza ' 'eof' 'ls'
		test_launch '1<<eof 2<<eof2 cat' 'olqsd' 'eof' 'tamer' 'eof2' 'ls'
		test_launch '1<<eof 2<<eof2 cat | wc' 'olqsd' 'eof' 'tamer' 'eof2' 'ls'
		test_launch '2<<eof 1<<eof2 cat' 'olqsd' 'eof' 'tamer' 'eof2' 'ls'
		test_launch '2<<eof 1<<eof2 cat | wc' 'olqsd' 'eof' 'tamer' 'eof2' 'ls'

	if [ ! -f ".fd" ] ; then
		echo "Can't find .fd executable" ;
	else
		launch "duplicating fd"
			test_launch "rm -f file" "./a.out 1 okalm > file ; cat file | wc ; rm file"
			test_launch "rm -f file" "./a.out 3 okalm 3>file ; cat file" "rm file"
			test_launch "rm -f file" "./a.out 5 string 3>f3 4>f4 5>f5" "echo 3 ; cat f3" "echo 4 ; cat f4" "echo 5 ; cat f5" "rm f3 f4 f5"
			test_launch "rm -f file" "./a.out 2 stre 2>&- 2>file ; cat file" "ls ;;; ls"
			test_launch "rm -f file" "./a.out 1 okalm 1>&- 1>&- 1>&2 1>&-"
			test_launch "rm -f file" "./a.out 4 okalm 4>&- 4>&- 4>&1 4>&-"
			test_launch "rm -f file" "./a.out 4 okalm 4>&1 4>&2 4>&3 3>file ; cat file ; rm file"
			test_launch "rm -f file" "./a.out 4 okalm 4>&1 4>&2 3>file ; cat file ; rm file"
	fi

	launch "asynchronous"
		test_launch "sleep 0.1 | ls ; echo lol"
		test_launch 'pwd ; cd ..  | echo | exit ; pwd'
		test_launch 'true | exit'
		test_launch 'yes | head -c1'

	rm -f file

finish
