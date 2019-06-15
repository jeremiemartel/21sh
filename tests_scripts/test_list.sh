# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_list.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 13:10:40 by jmartel           #+#    #+#              #
#    Updated: 2019/06/03 11:25:50 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Lists of commands"

## ; tests
	test 'ls -la ; pwd'
	test 'asd ; asd a ; qweqweqw ; pwd ; ls /'
	test 'echo okalm ; ls nofile ; pwd ; asdqw ; cat nofile'

## && tests
	test 'ls && pwd'
	test 'ls nofile && pwd && echo okalm'
	test 'echo okalm && ls nofile && echo okalm'
	test 'echo okalm && ls && echo okalm'
	test 'ecasd okalm && ls && echo okalm'

## || tests
	test 'ls || pwd'
	test 'ls nofile || echo okalm'
	test 'ls nofile || echo okalm || echo okalm'
	test 'ls -la || echo okalm || echo okalm'
	test 'lsasdqw -la || echqweo okalm || echo olm'

finish
