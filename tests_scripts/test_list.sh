# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_list.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 13:10:40 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 15:52:38 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Lists of commands"

## ; tests
	test_launch 'ls - ; pwd'
	test_launch 'asd ; asd a ; qweqweqw ; pwd ; ls /'
	test_launch 'echo okalm ; ls nofile ; pwd ; asdqw ; cat nofile'

## && tests
	test_launch 'ls && pwd'
	test_launch 'ls nofile && pwd && echo okalm'
	test_launch 'echo okalm && ls nofile && echo okalm'
	test_launch 'echo okalm && ls && echo okalm'
	test_launch 'ecasd okalm && ls && echo okalm'

## || tests
	test_launch 'ls || pwd'
	test_launch 'ls nofile || echo okalm'
	test_launch 'ls nofile || echo okalm || echo okalm'
	test_launch 'ls -a || echo okalm || echo okalm'
	test_launch 'lsasdqw -a || echqweo okalm || echo olm'

finish
