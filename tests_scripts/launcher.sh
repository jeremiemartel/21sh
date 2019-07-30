#!/bin/bash

compare_results()
{
	old_log_file="./log/prev"
	new_log_file="./log/new"

	new_ok=`grep -c OK $new_log_file`
	old_ok=`grep -c OK $old_log_file`
	new_ko=`grep -c KO $new_log_file`
	old_ko=`grep -c KO $old_log_file`

	segfault=`grep -c SEGFAULT $new_log_file`

	if [ "$old_ok" -ne "$new_ok" -o "$old_ko" -ne "$new_ko" ] ; then
		echo New Ok : $new_ok
		echo Old Ok : $old_ok
		echo ""
		echo New Ko : $new_ko
		echo Old Ko : $old_ko

		echo "Do you want to update log files ? (y)"
		read str
		if [ "$str" = "y" ] ; then
			mv $new_log_file $old_log_file
		fi

	else
		echo "OK ($new_ko failed tests)"
	fi
	if [ "$segfault" -ne 0 ] ; then
		echo $segfault SEGFAULT detected
	fi
}

compare_return_value()
{
	old_log_file="./log/ret_prev"
	new_log_file="./log/ret_new"

	if [ ! -e "$new_log_file" -o ! -e "$old_log_file" ] ; then
		echo "Can't find log files"
		return
	fi

	new_ok=`grep -c OK $new_log_file`
	old_ok=`grep -c OK $old_log_file`
	new_ko=`grep -c "BAD RETURNED VALUE" $new_log_file`
	old_ko=`grep -c "BAD RETURNED VALUE" $old_log_file`
	segfault=`grep -c SEGFAULT $new_log_file`

	if [ "$old_ok" -ne "$new_ok" -o "$old_ko" -ne "$new_ko" ]; then
		echo New Ok : $new_ok
		echo Old Ok : $old_ok
		echo ""
		echo New Ko : $new_ko
		echo Old Ko : $old_ko
		
		echo "Do you want to update log files ? (y)"
		read str
		if [ "$str" = "y" ] ; then
			mv $new_log_file $old_log_file
		fi
	else
		echo "OK ($new_ko failed tests)"
	fi

	if [ "$segfault" -ne 0 ] ; then
		echo $segfault SEGFAULT detected
	fi
}

if [ "$1" = "-r" ] ; then
	./start.sh -r -q 1>./log/ret_new
	compare_return_value
else
	./start.sh -q > log/new
	compare_results
fi
