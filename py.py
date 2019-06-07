#!/usr/bin/python

# cat includes/* | grep ');' > inc
# cat srcs/**/** | grep -v '**' > s

# fd = open("inc")
# line = fd.readline()
# while (line != ""):
# 	if (line[0] == '\t'):
# 		line = fd.readline()
# 		continue
# 	tab = line.split("\t")
# 	# print(tab)
# 	line = tab[len(tab) - 1]
# 	line = line.strip("\n;*")
# 	tab = line.split("(")
# 	line = tab[0]
# 	print(line)
# 	line = fd.readline()

import os
import re;

dir = "./srcs/"

#dir = "./srcs/expansions"
#header = "./includes/expansions.h"

format = "^(void|int|char|t_*)"

for filename in os.listdir(dir):
	if (os.path.isfile(os.path.join(dir, filename)) == False):
		continue
	fd = open(os.path.join(dir, filename))
	line1 = fd.readline()
	print("/*")
	print("**" + filename);
	print("*/")
	while (line1 != ""):
		if (re.search(format, line1) != None):
			print(line1.rstrip() + ';')
		line1 = fd.readline()
	print("")
