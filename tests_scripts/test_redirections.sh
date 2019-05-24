# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_redirections.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/05/23 14:04:56 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Redirections tests
launch "Redirections simple"
	test "echo Okalm > mybuf ; cat mybuf | wc -c ; rm mybuf"
	test "echo tamer > file ; <file wc | cat | wc"
	test "echo tamer > file ; <file wc | cat | wc > file ; ls -la file ; rm file"
finish