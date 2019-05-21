# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:19 by jmartel           #+#    #+#              #
#    Updated: 2019/05/21 15:58:20 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

launch()
{
	echo -e "${pink}$1 tests :${eoc}"
}

finish()
{
	echo ""
}

test()
{
	echo "$1" > buffer
	res=`diff <(<buffer ./21sh) <(<buffer bash)`
	if [ ! -z "$res" ] ; then
		echo -en "${red}KO${eoc}"
	else
		echo -en "${green}OK${eoc}"
	fi

	echo -e "\t${yellow}`cat buffer`${eoc}"
	rm buffer
}
