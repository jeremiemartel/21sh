# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 13:10:40 by jmartel           #+#    #+#              #
#    Updated: 2019/06/10 12:42:53 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Expansions tests
launch "Expansions"
	launch "Random"
	test 'echo $var'
									# test 'echo $TERM'
	test 'var=Okalm' 'echo $var'
	test 'var=Okalm' 'echo $var' 'var=po' 'echo $var'
	test 'var=Okalm' 'echo ${pwd:=ol}'
	test 'var=Okalm' 'echo ${'
	test 'w=' 'echo $w'
	test '${}' '$()'
	test '${)' '$}'

	launch "Hard"
									# test '321=asd' 'echo $321' '312=' 'echo $312'

	launch "List tests"
									# test 'ahsdiouashdiuasdhioasjdopasdjoldniouhjnqwioejqnwoel=adisuhiduashnodklajsodiajlsdlkasasdhuasodiu' 'echo $ahsdiouashdiuasdhioasjdopasdjoldniouhjnqwioejqnwoel='

finish
launch "Variables"
	launch "Basic"
	test 'var=okalm ; echo $var'
	test 'var=qwe 	&& echo $var'
	test 'var=asdqw || echo $vqr'
	test 'var1=okalmos' 'var2=speculos' 'echo $var1 $var2'
	test 'var1=okalmos' 'var2=speculos' 'echo $var1$var2'
	test 'var1=okalmos var2=speculos var3=O' 'echo $var1$var2$var3'
	test '=asd' '=' '12=we'
	test '-=qwe' '--=qwe' '"pwe=qwe"'
	test 'var=pwd' '$var'
	
	launch "#"
	# test 'var=Okalm' 'echo $#var $var'
	# test 'var=' 'echo $#var $var'
	test 'echo $s#var $var'
	# test 'var=asd' 'echo $#v#ar $v#ar'
	# test 'var=asd' 'echo #$#v#ar $v#ar'
	# test 'var=asd' 'echo #$#v#ar $v#ar#'
	test 'var=' 'echo $s#v#ar $v#ar'
	# test 'var=' 'echo #$#v#ar $v#ar'
	# test 'var=' 'echo #$#v#ar $v#ar#'
	# test 'echo $#v#ar $v#ar'
	test 'echo #$g#v#ar $v#ar'
	test 'echo #$d#v#ar $v#ar#'
	test 'echo #~$~d#v#ar $v#ar#'
	test 'echo #~$d~#~v#~ar $v~#ar#'

finish

