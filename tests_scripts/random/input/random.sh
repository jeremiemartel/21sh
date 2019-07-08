#!/bin/bash

#RANDOM_CHARS=" \"\'\\\`     qwertyuiopasdfghjklzxcvbnm1234567890!@#$%^&*()_+                       "
RANDOM_CHARS="\"\`\`\ [:blank:][:alnum:][:space:][:space:][:print:]\\\"\ "
RANDOM_LEN=30

res_file="../../test_random_input.sh"
#res_file="res"

green="\\033[32m"
yellow="\\033[33m"
red="\\033[31m"
eoc="\\033[0m"

random ()
{
	cat /dev/random | LC_CTYPE=C tr -dc "$RANDOM_CHARS" | head -c "$RANDOM_LEN"
}


if [ -e "$res_file" ] ; then
	echo $res_file already exists, do you want to erase it ?
	read ret
	if [ $ret = "y" ] ; then rm $res_file ;
	else exit ; fi
fi
touch $res_file

echo 'launch "random input"' >> $res_file

for i in {1..200} ; do
	RANDOM_LEN=$i
	for j in {1..20} ; do
		echo -n "test_launch '" >> $res_file
		rand=`random`
		echo -n $rand >> $res_file
		echo $rand
		echo "'" >> $res_file
	done
done

rm -f file
