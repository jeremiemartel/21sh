# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_tilde.sh                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/06 16:09:28 by jmartel           #+#    #+#              #
#    Updated: 2019/06/08 18:16:59 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Tilde expansion"
launch "Normal tests"
	test 'ls -la ~/'
	test 'ls ~' 'ls ~ '
	test 'echo ~'
	test 'asd ~/'
	test 'ls ~jmartel/'
	test 'echo ~asdqw/'
	test 'ls ~$2/'
	test 'cd ~d/' 'ls' 'cd ~/' 'ls'
	test 'ls -la ~$easd'

launch "Hard tests"
	test 'echo ~~~~~~~~'
	test 'echo ~~~~~~~~///////'
	test 'echo ~/~/~/~/~/~/~/~/'
	test 'echo /~'
	test 'echo asdq~'
	test 'echo weq~asd'
	test 'echo okalm~'
	test 'echo ~oadasd'

launch "Quote tests"
				# test 'echo ~as\dasdas/'
				# test 'echo ~as"dasd"as/'
	test 'echo ~    /~ /~ "~"'
	test 'echo "~"\~'
finish