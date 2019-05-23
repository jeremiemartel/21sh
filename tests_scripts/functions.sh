# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:19 by jmartel           #+#    #+#              #
#    Updated: 2019/05/23 17:06:04 by jmartel          ###   ########.fr        #
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
	for i in "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9" "${10}"
	do
		if [ -n "$i" ] ; then 
			echo "${i}" >> buffer ; fi;
	done

	res=`diff <(<buffer bash 2>res2.bash) <(<buffer ./21sh 2>res2.21sh)`

	if [ ! -z "$res" ] ; then
		echo -e "${red}KO${eoc}"
		echo -e "${yellow}`cat buffer`${eoc}"
	elif [ ! -z "`diff res2.bash res2.21sh`" ] ; then 
		res=`diff res2.bash res2.21sh`
		echo -e "${red}KO${eoc}"
		echo -e "${yellow}`cat buffer`${eoc}"
		if [ -n $verbose ] ; then
			echo -e "${cyan}`echo $res`${eoc}"
		fi
		rm res2.bash res2.21sh
	else
		echo -e "${green}OK${eoc}"
	fi

	rm buffer
}
