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
	test_launch '"e"c"h"o lol'
	test_launch '"echo" lol'
	test_launch '""echo""  "" lol'
	test_launch '""echo"" "lol"'
	test_launch '"ech"o Okalm'

	test_launch '"e"c"h"o lol'
	test_launch '"e"c"h"o lol'
	test_launch '"e"c"h"o lol'

	launch "Random"
	test_launch '"var=pwe"'
	test_launch 'ls ""'

finish
