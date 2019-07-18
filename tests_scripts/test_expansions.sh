# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 13:10:40 by jmartel           #+#    #+#              #
#    Updated: 2019/06/20 13:35:36 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Expansions tests
launch "Expansions"
	launch "Random"
	test_launch 'echo $var'
									test_launch 'echo $TERM'
	test_launch 'var=Okalm' 'echo $var'
	test_launch 'var=Okalm' 'echo $var' 'var=po' 'echo $var'
	test_launch 'var=Okalm' 'echo ${pwd:=ol}'
	test_launch 'var=Okalm' 'echo ${'
	test_launch 'w=' 'echo $w'
	test_launch '${}'
	test_launch '${)' '$}'
	test_launch '$novar ls'
	test_launch	'$pwd $pwd'

	launch "List tests"
	test_launch 'ahsdiouashdiuasdhioasjdopasdjoldniouhjnqwioejqnwoel=adisuhiduashnodklajsodiajlsdlkasasdhuasodiu' 'echo $ahsdiouashdiuasdhioasjdopasdjoldniouhjnqwioejqnwoel='

finish

launch "Variables"
	launch "Basic"
	test_launch '=qsda'
	test_launch 'var=okalm ; echo $var'
	test_launch 'var=qwe 	&& echo $var'
	test_launch 'var=asdqw || echo $vqr'
	test_launch 'var1=okalmos' 'var2=speculos' 'echo $var1 $var2'
	test_launch 'var1=okalmos' 'var2=speculos' 'echo $var1$var2'
	test_launch 'var1=okalmos var2=speculos var3=O' 'echo $var1$var2$var3'
	test_launch '=asd' '=' '12=we'
	test_launch '-=qwe' '--=qwe' '"pwe=qwe"'
	test_launch 'var=pwd' '$var'
	
	launch "#"
	test_launch 'var=Okalm' 'echo $#var $var'
	test_launch 'var=' 'echo $#var $var'
	test_launch 'echo $s#var $var'
	test_launch 'var=asd' 'echo $#v#ar $v#ar'
	test_launch 'var=asd' 'echo #$#v#ar $v#ar'
	test_launch 'var=asd' 'echo #$#v#ar $v#ar#'
	test_launch 'var=' 'echo $s#v#ar $v#ar'
	test_launch 'var=' 'echo #$#v#ar $v#ar'
	test_launch 'var=' 'echo #$#v#ar $v#ar#'
	test_launch 'echo $#v#ar $v#ar'
	test_launch 'echo #$g#v#ar $v#ar'
	test_launch 'echo #$d#v#ar $v#ar#'
	test_launch 'echo #~$~d#v#ar $v#ar#'
	test_launch 'echo #~$d~#~v#~ar $v~#ar#'

	launch "Special Variables"
	test_launch 'echo $?'
	test_launch 'echo $? ; ls ; echo $?'
	test_launch 'echo $? ; ls asdqwe ; echo $?'
	test_launch 'echo $? ; okalm ; echo $?'
	test_launch 'echo $? ; echo $?'
	test_launch 'touch file ; chmod 666 file' './file ; echo $?' 'rm file'

# launch "Deprecated"
	# launch "Hard"
	# test_launch '321=asd' 'echo $321' '312=' 'echo $312'


finish

