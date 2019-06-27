# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_redirections.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 15:52:38 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Redirections tests
launch "Redirections simple"
	test_launch "echo Okalm > mybuf ; cat mybuf | wc -c ; rm mybuf"
	test_launch "echo tamer > file ; <file wc | cat | wc ; rm file"
	test_launch "echo tamer > file ; <file wc | cat | wc > file ; ls -a file ; rm file"
	test_launch "echo lol > file ; echo lalala | cat < file ; rm file"

## here doc
	test_launch "cat <<eoc" "ls -a" "okalm" "eoc"
	test_launch "ls <<eoc" "ls -a" "okalm" "eoc"
	test_launch "cat <<eoc 1>file1 2>file2" "ls -a" "okalm" "eoc" "cat file1" "cat file2" "rm file1 file2"
	test_launch "cat <<   eoc 1>file1 2>file2" "ls -a" "okalm" "eoc" "cat file1" "cat file2" "rm file1 file2"
	test_launch "cat <<   Okalm" "ls -a" "okalm" " Okalm" "Okalm " "Okalm"

## Closing fd
	test_launch "echo lol 1>&-" "ls -a"
	test_launch "ls nofile 2>&-"

## Hard
	test_launch "echo lol > file ; echo lal > file2 ;  cat < file2 | cat -e < file ; rm file ; rm file2"
	test_launch "echo lol > file ; cat < file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test_launch "echo lol > file ; cat -e < file << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test_launch "echo lol > file ; cat -e < file << eoc  < file ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test_launch "echo lol > file ; cat file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test_launch "echo lol > file ; cat file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "not a eoc"
	test_launch "ls -a . nofile > file 2>&1 ; rm file"
	test_launch "ls -a . nofile 2>&1 > file ; rm file"
	test_launch "echo lol >&- file"
	test_launch "echo lol >>"
	test_launch "cat <<"
	test_launch "cat 1<&"
	test_launch "cat 1<&"
	test_launch "cat <&"
	test_launch "touch file ; cat < file >&- ; rm file"
	test_launch "echo lol > file ; cat < file <&- ; rm file"
	test_launch "echo \"lol iuuiuiu\" > file ; cat < file | cat -e >> file ; cat file ; rm file"
finish
