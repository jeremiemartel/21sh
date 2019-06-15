# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_exec.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:41 by jmartel           #+#    #+#              #
#    Updated: 2019/06/15 15:35:50 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch "exec"
	launch "Basic"
	test 'touch exec' './exec' 'rm exec'
	test 'touch exec ; chmod 000 exec' './exec' 'chmod 777 exec ; rm exec'
	test 'touch exec ; chmod +x exec' './exec' 'rm exec'
	test 'mkdir dir'  './dir' 'rm -r dir'
	test 'rm -rf dir'
	test './nofile'
	test './functions.sh'
finish
