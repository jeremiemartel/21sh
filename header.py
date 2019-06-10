#!/usr/bin/python
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    header.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/09 18:08:45 by jmartel           #+#    #+#              #
#    Updated: 2019/06/09 18:08:45 by jmartel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import re;

dir = "./srcs/"

#dir = "./srcs/expansions"
#header = "./includes/expansions.h"

format = "^(void|int|char|t_*)"
res = open("res", 'w')

def read_dir(filename):
	res = {}
	for filename in os.listdir(dir):
		if (os.path.isfile(os.path.join(dir, filename)) == False):
			continue
		fd = open(os.path.join(dir, filename))
		line1 = fd.readline()
		content = []
		while (line1 != ""):
			if (re.search(format, line1) != None):
				prototype = line1.rstrip()
				prototype = prototype.split('\t')
				prototype = [i for i in prototype if (i != "")]
				buffer = {"type" : prototype[0], "name" : prototype[1]}
				content.append(buffer)
			line1 = fd.readline()
		res[filename] = content
	return (res)

def format_dir(dir_data):
	res = ""
	max_tabs = 0
	for file in dir_data:
		for function in dir_data[file]:
			length = len(function["type"])
			tabs = length // 4
			if (length % 4):
				tabs += 1
			if (tabs > max_tabs):
				max_tabs = tabs
	tabs = "\t" * max_tabs
	for file in dir_data:
		res += "*/\n** " + file + "\n*/\n"
		print(file + ":")
		for function in dir_data[file]:
			str = function["type"]
			str += "\t" * (max_tabs - (len(function["type"]) // 4) + 1)
			str += function["name"]
			str += ";\n"
			res += str
		res += "\n"
	return res

dir_data = read_dir("./srcs/expansions")
res = format_dir(dir_data)

header = open("header", "w")
header.write(res)
