# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 13:10:40 by jmartel           #+#    #+#              #
#    Updated: 2019/06/06 16:38:58 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Expansions tests
launch "Expansions"
	launch "Simple"
	test 'echo $var'
	test 'echo $TERM'
	test 'var=Okalm' 'echo $var'
	test 'var=Okalm' 'echo $var' 'var=po' 'echo $var'
	test 'var=Okalm' 'echo ${pwd:=ol}'
	test 'var=Okalm' 'echo ${'
	test 'w=' 'echo $w'
	test '${}' '$()'
	test '${)' '$}'

	launch "Hard"
	test '=asd' '=' '12=we'
	test '321=asd' 'echo $321' '312=' 'echo $312'
	test '-=qwe' '--=qwe' '"pwe=qwe"'

	launch "List tests"
	test 'var=pwd' '$var'
	test 'ahsdiouashdiuasdhioasjdopasdjoldniouhjnqwioejqnwoel=adisuhiduashnodklajsodiajlsdlkasasdhuasodiu' 'echo $ahsdiouashdiuasdhioasjdopasdjoldniouhjnqwioejqnwoel='
	test 'var=okalm ; echo $var'
	test 'var=qwe 	&& echo $var'
	test 'var=asdqw || echo $vqr'
finish

