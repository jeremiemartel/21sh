#!/bin/bash

#RANDOM_CHARS=" \"\'\\\`     qwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*()_+                       "
RANDOM_CHARS="\"\ \ \ lasd"
RANDOM_LEN=30

res_file="../../test_random_quotes.sh"
buffer_dir="sandbox"

green="\\033[32m"
yellow="\\033[33m"
red="\\033[31m"
eoc="\\033[0m"

random ()
{
	cat /dev/random | LC_CTYPE=C tr -dc "$RANDOM_CHARS" | head -c "$RANDOM_LEN"
}

if [ -e "$res_file" ] ; then rm $res_file ; fi
touch $res_file

if [ ! -d "$buffer_dir" ] ; then mkdir $buffer_dir ; fi

echo 'launch "random input"' >> $res_file

for i in {1..200} ; do
	RANDOM_LEN=$i
	for j in {1..20} ; do
		buffer="${i}_${j}"
		buffer_path="`pwd`/${buffer_dir}/${buffer}"
		echo "test_launch_pipe \"${buffer_path}\"" >> $res_file
		rand=`random`
		echo $rand >> ${buffer_dir}/$buffer
		echo "$buffer : $rand"
	done
done

