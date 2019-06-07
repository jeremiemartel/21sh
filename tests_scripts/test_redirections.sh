# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_redirections.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/05/29 12:33:22 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Redirections tests
launch "Redirections simple"
	test "echo Okalm > mybuf ; cat mybuf | wc -c ; rm mybuf"
	test "echo tamer > file ; <file wc | cat | wc"
	test "echo tamer > file ; <file wc | cat | wc > file ; ls -la file ; rm file"
	test "echo lol > file ; echo lalala | cat < file ; rm file"

## here doc
	test "cat <<eoc" "ls -la" "okalm" "eoc"
	test "ls <<eoc" "ls -la" "okalm" "eoc"
	test "cat <<eoc 1>file1 2>file2" "ls -la" "okalm" "eoc" "cat file1" "cat file2" "rm file1 file2"
	test "cat <<   eoc 1>file1 2>file2" "ls -la" "okalm" "eoc" "cat file1" "cat file2" "rm file1 file2"
	test "cat <<   Okalm" "ls -la" "okalm" " Okalm" "Okalm " "Okalm"

## Closing fd
	test "echo lol 1>&-" "ls -la"
	test "ls nofile 2>&-"

## Hard
	test "echo lol > file ; echo lal > file2 ;  cat < file2 | cat -e < file ; rm file ; rm file2"
	test "echo lol > file ; cat < file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test "echo lol > file ; cat -e < file << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test "echo lol > file ; cat -e < file << eoc  < file ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test "echo lol > file ; cat file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "eoc"
	test "echo lol > file ; cat file | cat -e << eoc ; rm file" "heredoc_1" "heredoc_2" "not a eoc"
	test "ls -la . nofile > file 2>&1 ; rm file"
	test "ls -la . nofile 2>&1 > file ; rm file"
	test "echo lol >&- file"
	test "echo lol >>"
	test "cat <<"
	test "cat 1<&"
	test "cat 1<&"
	test "cat <&"
	test "touch file ; cat < file >&- ; rm file"
	test "echo lol > file ; cat < file <&- ; rm file"
	test "echo \"lol iuuiuiu\" > file ; cat < file | cat -e >> file ; cat file ; rm file"
finish
