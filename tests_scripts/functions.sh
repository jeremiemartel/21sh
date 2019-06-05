# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:19 by jmartel           #+#    #+#              #
#    Updated: 2019/06/05 23:35:46 by jmartel          ###   ########.fr        #
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
	diff_tried=$((diff_tried+1))
	res=`diff <(<buffer bash 2>res2.bash) <(<buffer ./21sh 2>res2.21sh)`

	if [ ! -z "$res" ] ; then
		echo -e "${red}KO${eoc}"
		if [ -n "$verbose" ] ; then
			echo -e "${yellow}`cat buffer`${eoc}"
		fi
	elif [ "${test_stderr}" -ne 0 ] && [ ! -z "`diff res2.bash res2.21sh`" ] ; then 
		res=`diff res2.bash res2.21sh`
		echo -e "${red}KO${eoc}"
		if [ -n "$verbose" ] ; then
			echo -e "${yellow}`cat buffer`${eoc}"
			echo -e "${cyan}`echo $res`${eoc}"
		fi
	else
		echo -e "${green}OK${eoc}"
		diff_passed=$((diff_passed+1))
	fi
	rm -f res2.bash res2.21sh

	if [ ! -z $valgrind ] ; then
		tried=$((tried+1))
		tmp_log_file="tmp_log"
		inner_log_dir="${log_dir}/test_${tried}"
		error_exit_code=17
		valgrind --leak-check=full --suppressions=$suppressions_file \
			--error-exitcode=$error_exit_code --log-file=$tmp_log_file ./21sh < buffer >/dev/null 2>&1
		ret=$?
		if [ $ret -eq $error_exit_code ] || ([ ! $ret -eq 1 ] && [ ! $ret -eq 0 ]) ; then
			echo -e "${red}valgrind error, tracing logs at ${inner_log_dir}${eoc}"
			echo -e "${yellow}`cat buffer`${eoc}"
			mkdir -p $inner_log_dir
			cat buffer > ${inner_log_dir}/failed_script
			cat $tmp_log_file > ${inner_log_dir}/valgrind_trace
		else
			echo -e "${green}no valgrind errors${eoc}"
			passed=$((passed+1))
		fi
		rm $tmp_log_file
	fi
	rm buffer
}
