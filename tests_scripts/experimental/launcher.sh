#!/bin/bash

dir=".."
for file in `ls $dir/test_*.sh`
do
	        ln -s $file . 2>/dev/null
done

./start.sh -q > log/new
./res.sh
