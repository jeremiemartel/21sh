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
import re
import sys

format = "^(static|void|int|char|t_*)"

def recursive_list_dir(dirpath, filepaths):
	for filename in os.listdir(dirpath):
		filepath = os.path.join(dirpath, filename)
		if (os.path.isdir(filepath) == True):
			recursive_list_dir(filepath, filepaths)
		elif (os.path.isfile(filepath) == True):
			if (filename[-1] == 'c' and filename[-2] == '.'):
				filepaths.append(filepath)
	return (filepaths)

def get_file_names():
	dirname = []
	if (len(sys.argv) > 1):
		for i in range(1, len(sys.argv)):
			dirname.append(sys.argv[i])
	else :
		dirname = ["."]
	filepaths = []
	for dir in dirname:
		if (os.path.isdir(dir)):
			recursive_list_dir(dir, filepaths)
		else :
			filepaths.append(dir)
	return (filepaths)

def read_file(filepath):
	content = []
	if (os.path.isfile(filepath) == False):
		return (content)
	fdr = open(filepath, 'r')
	line = fdr.readline()
	while (line != ""):
		content.append(line)
		line = fdr.readline()
	fdr.close()
	return (content)

def norminette_line_len(line):
	line_len = 0
	tab_len = 4
	for i in range(len(line)):
		if (line[i] == '\t'):
			line_len += tab_len
			tab_len = 4
		else :
			if (tab_len > 0):
				tab_len -= 1
			else :
				tab_len = 3
			line_len += 1
	return line_len

def norminette(filename, content):
	funclen = -1
	funcname = ""
	funcnumber = 0
	errors = 0
	messages = []
	for i in range(len(content)):
		## Multiple empty lines
		if (content[i] == content[i - 1] == "\n"):
			messages.append("\t{:-3d}: multiple empty lines".format(i + 1 ))
		## Line len
		line_len = norminette_line_len(content[i])
		if (line_len > 81):
			messages.append("\t{:-3d}: line is too long ({:d})".format(i + 1, line_len - 1)) ## -1 ??
		## Functions len and declaration
		if (re.search(format, content[i]) != None):
			prototype = content[i].rstrip()
			prototype = prototype.split('\t')
			prototype = [k for k in prototype if (k != "")]
			if (len(prototype) < 2):
				messages.append("\t{:-3d}: bad declaration: {:s}".format(i + 1, prototype[0]))
				return
			funcname = prototype[1]
			funcname = funcname.split('(')[0]
			funcnumber += 1
		elif (content[i] == '{\n'):
			funclen = 0
		elif (content[i] == '}\n'):
			if (funclen > 25):
				messages.append("\t{:-3d}: {:s}: {:d} lines".format(i - funclen - 1, funcname, funclen))
			funclen = -1
		elif (funclen >= 0):
			funclen += 1
		if (content[int(i)].find('//') != -1):
			messages.append("\t{:-3d}: c++ comment".format(i))
	if (funcnumber > 5):
		messages.append("\t{:d} functions in file".format(funcnumber))
	if (len(messages) > 0):
		print(filename)
		for msg in messages:
			print(msg)


def main():
	filepaths = get_file_names()
	for filepath in filepaths:
		if (filepath[-1] != 'c' or filepath[-2] != '.'):
			continue
		content = read_file(filepath)
		if (not content):
			continue
		norminette(filepath, content)

main()