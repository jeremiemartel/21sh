# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_lexer.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/06/10 11:19:09 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "Lexer"
	launch "Random"
	test '"var=pwe"'
	test 'ls ""'
finish
