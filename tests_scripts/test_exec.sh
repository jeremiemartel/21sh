# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_exec.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/07/05 16:39:13 by jmartel          ###   ########.fr        #
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
	test_launch '" ls "' 'echo $?' '"ls "' 'echo $?'

	launch "Permissions"
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 777 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 600 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 500 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 400 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 300 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 200 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 100 file' './file' 'chmod 777 file ; rm file'
	test_launch 'echo "#!/bin/bash" >file' 'echo "echo lol" >> file' 'chmod 000 file' './file' 'chmod 777 file ; rm file'

	launch "execve fail"
	if [ ! -f "execve_fail" ] ; then echo -e ${RED}"CANNOT FIND EXECVE_FAIL BINARY"${EOC}
	else
		test_launch './execve_fail'
		test_launch 'PATH=.:/usr/bin' 'execve_fail'
		test_launch 'env ./execve_fail'
		test_launch 'PATH=.:/usr/bin' 'env execve_fail'
		test_launch './execve_fail | wc'
		test_launch 'PATH=.:/usr/bin' 'execve_fail | wc'
		test_launch 'env ./execve_fail | wc'
		test_launch 'PATH=.:/usr/bin' 'env execve_fail | wc'

	fi
finish
