# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_expansions_param.sh                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:00:50 by jmartel           #+#    #+#              #
#    Updated: 2019/06/06 16:57:01 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Redirections tests
launch "Parameter expansion"
	launch ":- and -"
	## :- and -
	test 'var=wea' 'echo ${var:-okalm}'
	test 'var=wea' 'echo ${var-okalm}'
	test 'var=' 'echo ${var:-okalm}'
	test 'var=' 'echo ${var-okalm}'
	test 'echo ${var:-okalm}'
	test 'echo ${var-okalm}'
	test 'qweqweqwe=wea' 'echo ${qweqweqwe:-okalm}'
	test 'qweqweqwe=wea' 'echo ${qweqweqwe-okalm}'
	test 'qweqweqwe=' 'echo ${qweqweqwe:-okalm}'
	test 'qweqweqwe=' 'echo ${qweqweqwe-okalm}'
	test 'echo ${qweqweqwe:-okalm}'
	test 'echo ${qweqweqwe-okalm}'

	test 'echo ${-}'
	test 'echo ${:-}'
	test 'echo ${sd-}'
	test 'echo ${sd:-}'
	test 'echo ${-asd}'
	test 'echo ${:-asd}'

	launch ":= and ="
	## := and =
	test 'var=wea' 'echo ${var:=okalm}'
	test 'var=wea' 'echo ${var=okalm}'
	test 'var=' 'echo ${var:=okalm}'
	test 'var=' 'echo ${var=okalm}'
	test 'echo ${var:=okalm}'
	test 'echo ${var=okalm}'
	test 'qweqweqwe=wea' 'echo ${qweqweqwe:=okalm}'
	test 'qweqweqwe=wea' 'echo ${qweqweqwe=okalm}'
	test 'qweqweqwe=' 'echo ${qweqweqwe:=okalm}'
	test 'qweqweqwe=' 'echo ${qweqweqwe=okalm}'
	test 'echo ${qweqweqwe:=okalm}'
	test 'echo ${qweqweqwe=okalm}'

	test 'echo ${=}'
	test 'echo ${:=}'
	test 'echo ${sd=}'
	test 'echo ${sd:=}'
	test 'echo ${=asd}'
	test 'echo ${:=asd}'

	launch ":? and ?"
	## :? and ?
	test 'var=wea' 'echo ${var:?okalm}'
	test 'var=wea' 'echo ${var?okalm}'
	test 'var=' 'echo ${var:?okalm}'
	test 'var=' 'echo ${var?okalm}'
	test 'echo ${var:?okalm}'
	test 'echo ${var?okalm}'
	test 'qweqweqwe=wea' 'echo ${qweqweqwe:?okalm}'
	test 'qweqweqwe=wea' 'echo ${qweqweqwe?okalm}'
	test 'qweqweqwe=' 'echo ${qweqweqwe:?okalm}'
	test 'qweqweqwe=' 'echo ${qweqweqwe?okalm}'
	test 'echo ${qweqweqwe:?okalm}'
	test 'echo ${qweqweqwe?okalm}'

	test 'echo ${?}'
	test 'echo ${:?}'
	test 'echo ${sd?}'
	test 'echo ${sd:?}'
	test 'echo ${?asd}'
	test 'echo ${:?asd}'

	launch ":+ and +"
	## :+ and +
	test 'var=wea' 'echo ${var:+okalm}'
	test 'var=wea' 'echo ${var+okalm}'
	test 'var=' 'echo ${var:+okalm}'
	test 'var=' 'echo ${var+okalm}'
	test 'echo ${var:+okalm}'
	test 'echo ${var+okalm}'
	test 'qweqweqwe=wea' 'echo ${qweqweqwe:+okalm}'
	test 'qweqweqwe=wea' 'echo ${qweqweqwe+okalm}'
	test 'qweqweqwe=' 'echo ${qweqweqwe:+okalm}'
	test 'qweqweqwe=' 'echo ${qweqweqwe+okalm}'
	test 'echo ${qweqweqwe:+okalm}'
	test 'echo ${qweqweqwe+okalm}'

	test 'echo ${+}'
	test 'echo ${:+}'
	test 'echo ${sd+}'
	test 'echo ${sd:+}'
	test 'echo ${+asd}'
	test 'echo ${:+asd}'

	launch "Quoting tests"
	test 'echo ${""}'
	test 'echo ${\}ls:=sd}'
	test 'echo ${"wd"sd:+okalm}'
	test 'wd=adq''echo ${"wd"sd:+okalm}'
	test 'echo ${"wd"sd:+okalm}'

	launch "Random"
	## Invalid tests
	test 'echo ${}'
	test 'echo ${'
	test 'echo $}'
	test 'echo ${()}'
	test 'echo ${asdw+}'
	test 'echo ${:asd}'
	test 'echo ${:}'
	test 'echo ${s:}'
	## Valid tests
	test 'echo ${X:=abc}'
	test 'echo ${posix:?}'
	test 'echo ${3:+posix}'
	test 'echo ${#HOME}'
	test 'echo ${x#$HOME}'
	test 'dest="/backups"' 'printf "$dest"'
	test 'echo ${USER:=foo}'
	test 'echo ${USER:=foo}'
	test 'echo ${x%.c}.o'
finish
