# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_lexer.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 13:35:36 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Lexer"
	launch "Quotes"
	test_launch '"e"c"h"o lol' 'ls'
	test_launch '"echo" lol' 'ls'
	test_launch '""echo""  "" lol' 'ls'
	test_launch '""echo"" "lol"' 'ls'
	test_launch '"ech"o Okalm' 'ls'
	test_launch '"e"c"h"o lol' 'ls'
	test_launch '"e"c"h"o lol' 'ls'
	test_launch '"e"c"h"o lol' 'ls'
	test_launch '""""""ec""""h""o lol' 'ls'
	test_launch 'ec"ho lol' 'ls'

	launch
	test_launch '\ls \$HOME'
	test_launch '\ls $\H\O\M\E'
	test_launch 'l\s $HOME\'
	test_launch '""'
	test_launch '"\\\""\\ls'

	launch "Random"
	test_launch '"var=pwe"'
	test_launch 'ls ""'

finish
