# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_exec.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 13:35:36 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "exec"
	launch "Basic"
	test_launch 'touch exec' './exec' 'rm exec'
	test_launch 'touch exec ; chmod 000 exec' './exec' 'chmod 777 exec ; rm exec'
	test_launch 'touch exec ; chmod +x exec' './exec' 'rm exec'
	test_launch 'mkdir dir'  './dir' 'rm -r dir'
	test_launch 'rm -rf dir'
	test_launch './nofile'
	test_launch './functions.sh'

	launch "Permissions"
	test_launch 'echo "echo lol" > file' 'chmod 777 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "echo lol" > file' 'chmod 600 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "echo lol" > file' 'chmod 500 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "echo lol" > file' 'chmod 400 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "echo lol" > file' 'chmod 300 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "echo lol" > file' 'chmod 200 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "echo lol" > file' 'chmod 100 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "echo lol" > file' 'chmod 000 file' './file' 'chmod 777 file ; rm file'

finish