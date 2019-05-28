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
	test "ls -la . not_existing_file > file 2>&1 ; rm file"
	test "ls -la . not_existing_file 2>&1 > file ; rm file"
	test "echo lol > file ; echo lalala | cat < file ; rm file"
	test "echo lol > file ; echo lal > file2 ;  cat < file2 | cat -e < file ; rm file ; rm file2"
	test "echo lol > file ; cat < file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test "echo lol > file ; cat -e < file << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test "echo lol > file ; cat -e < file << eoc  < file ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test "echo lol > file ; cat file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test "echo lol > file ; cat file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "not a eoc"
finish
