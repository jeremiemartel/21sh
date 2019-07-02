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
	if (len(sys.argv) > 1):
		dirname = sys.argv[1]
	else :
		dirname = "."
	if (os.path.isdir(dirname) == False):
		print("Invalid directory")
		exit(1)
	filepaths = []
	recursive_list_dir(dirname, filepaths)
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

def norminette(filename, content):
	print(filename)
	funclen = -1
	funcname = ""
	funcnumber = 0
	for i in range(len(content)):
		if (len(content[i]) > 81):
			print("\t{:-3d}: line is too long ({:d})".format(i + 1, len(content[i]) - 1))
		if (re.search(format, content[i]) != None):
			prototype = content[i].rstrip()
			prototype = prototype.split('\t')
			prototype = [k for k in prototype if (k != "")]
			if (len(prototype) < 2):
				print("\t{:-3d}: bad declaration: {:s}".format(i + 1, prototype[0]))
				return
			funcname = prototype[1]
			funcname = funcname.split('(')[0]
			funcnumber += 1
		elif (content[i] == '{\n'):
			funclen = 0
		elif (content[i] == '}\n'):
			if (funclen > 25):
				print("\t{:-3d}: {:s}: {:d} lines".format(i - funclen - 1, funcname, funclen))
			funclen = -1
		elif (funclen >= 0):
			funclen += 1
		if (content[int(i)].find('//') != -1):
			print("\t{:-3d}: c++ comment".format(i))
	if (funcnumber > 5):
		print("\t{:d} functions in file".format(funcnumber))

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