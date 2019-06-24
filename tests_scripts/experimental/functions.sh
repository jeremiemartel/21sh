# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 15:58:19 by jmartel           #+#    #+#              #
#    Updated: 2019/06/10 09:49:29 by jmartel          ###   ########.fr        #
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

echo_ok()
{
	if [ -n "$show_error" ] ; then
		echo -e ${green}"OK"${eoc}
	fi
	diff_passed=$((diff_passed+1))
}

diff_files()
{
	res=`diff $1 $2`
	if [ -n "$res" ] ; then
		echo -e "${red}KO${eoc}"
		if [ -n "$verbose" ] ; then
			echo -e "${yellow}`cat buffer`${eoc}"
			echo -e "${cyan}" `cat $1` "${eoc}"
			echo -e "${cyan}" `cat $2` "${eoc}"
		fi
		return 1
	fi
	return 0
}

valgrind_test()
{
		tried=$((tried+1))
		tmp_log_file="tmp_log"
		inner_log_dir="${log_dir}/test_${tried}"
		error_exit_code=17
		valgrind --leak-check=full --suppressions=$suppressions_file \
			--error-exitcode=$error_exit_code --log-file=$tmp_log_file ./21sh < buffer >/dev/null 2>&1
		ret=$?
		if [ $ret -eq $error_exit_code ] || ([ $ret -ne 1 ] && [ $ret -ne 0 ]) ; then
			echo -e "${red}valgrind error, tracing logs at ${inner_log_dir}${eoc}"
			echo -e "${yellow}`cat buffer`${eoc}"
			mkdir -p $inner_log_dir
			cat buffer > ${inner_log_dir}/failed_script
			cat $tmp_log_file > ${inner_log_dir}/valgrind_trace
			rm -f $tmp_log_file
		else
			echo -e "${green}no valgrind errors${eoc}"
			passed=$((passed+1))
			rm -f $tmp_log_file
		fi
}

check_ret_value()
{
	ret=$?
	ret=$((ret & 0x0F))
	if [ $ret -eq 0 ] ; then return 0 ; fi
	if [ $ret -eq 11 ] || [ "ret" -eq 10 ] ; then 
		echo -e "${red}SEGFAULT${eoc}"
		return 1
	fi
	return 0
}

test_launch()
{
	echo "$1" > buffer
	for i in "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9"
	do
		if [ -n "$i" ] ; then 
			echo "${i}" >> buffer ; fi;
	done
	diff_tried=$((diff_tried+1))
	touch res1.bash res2.bash res1.21sh res2.21sh
	<buffer bash 1>res1.bash 2>res2.bash
	<buffer ./${exec} 1>res1.21sh 2>res2.21sh

	continue=0
# echo "continue (return): $continue"
	check_ret_value
	continue=$?

# echo "continue (stdout): $continue"
	if [ 0 -eq "$continue" ] ; then
		diff_files res1.21sh res1.bash
		continue=$?
	fi
# echo "continue (stderr): $continue"
	if [ 0 -eq "$continue" ] && [ -n "${test_stderr}" ] ; then
		diff_files res2.21sh res2.bash
		continue=$?
	fi
# echo "continue (ok): $continue"
	if [ 0 -eq "$continue" ] ; then
		echo_ok
	fi
# echo "continue (valgrind): $continue"
	if [ -n "$valgrind" ] ; then
		valgrind_test
	fi

	rm -f buffer
	rm -f res1.bash res1.21sh
	rm -f res2.bash res2.21sh
}
