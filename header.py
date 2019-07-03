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

format = "^(void|int|char|t_*)"

ignored_files=["grammar.c"]

## read_dir(filename):
##	open every files in dir argument, if file is valid it's extracts prototypes
##	using regex. it stocked in a dictionnary using filenames as keys, every value
##	is a dictionnary with keys "type"  :int, char, void, ...
##	and prototype foo(bar, foo)

def read_dir(dir):
	res = {}
	for filename in os.listdir(dir):
		if (os.path.isfile(os.path.join(dir, filename)) == False):
			continue
		if (filename in ignored_files):
			continue
		fd = open(os.path.join(dir, filename))
		line1 = fd.readline()
		content = []
		while (line1 != ""):
			if (re.search(format, line1) != None):
				prototype = line1.rstrip()
				while (prototype[-1] != ")"):
					buffer = fd.readline()
					buffer = buffer.strip()
					prototype += " " + buffer
				prototype = prototype.split('\t')
				prototype = [i for i in prototype if (i != "")]
				buffer = {"type" : prototype[0], "name" : prototype[1]}
				content.append(buffer)
			line1 = fd.readline()
		res[filename] = content
	return (res)

## format_dir_datas
##	create from formated string, ready to print in header, read_dir datas
def format_dir_datas(dir_data, tab_offset):
	res = ""
	max_tabs = tab_offset
	if (max_tabs == 0):
		max_tabs = 2
	## Determine maximum number of tabs to add
	for file in dir_data:
		for function in dir_data[file]:
			length = len(function["type"])
			tabs = length // 4
			if (length % 4):
				tabs += 1
			if (tabs > max_tabs):
				max_tabs = tabs

	## Create every file list of prototypes	
	tabs = "\t" * max_tabs
	for file in dir_data:
		res += "/*\n** " + file + "\n*/\n"
		for function in dir_data[file]:
			str = function["type"]
			str += "\t" * (max_tabs - (len(function["type"]) // 4))
			str += function["name"]
			str += ";\n"
			if (len(str) + 3 * max_tabs >= 80):
				str = function["type"]
				str += "\t" * (max_tabs - (len(function["type"]) // 4))
				str += function["name"].split("(", 1)[0]
				str += "(\n\t"
				# str += function["name"].split("(", 1)[1].strip()
				buff = function["name"].split("(", 1)[1].strip()
				if (len(buff) + 3 * max_tabs >= 80):
					for a in buff.split(","):
						str += a.strip()
						if (a.strip()[-1] == ')'):
							str += ";\n"
						else :
							str += ",\n\t"
				else :
					str += buff + ";\n"
			res += str
		res += "\n"
	return res

def create_header(header, datas):
	# Open header in reading mode
	fd_header = open(header, 'r')
	header_content = ""
	line = fd_header.readline()

	# Read file until header delimitation or end of file
	while (line != ""):
		header_content += line
		if (line.strip() == "*" * 80):
			header_content += "*/\n\n"
			break
		line = fd_header.readline()

	# Add header delimitation if do not exists
	if (line == ""):
		header_content += "/*\n"
		header_content += "*" * 80 + "\n"
		header_content += "*/\n\n"

	# Add datas to content
	header_content += datas
	header_content += "#endif\n"
	return header_content

def write_header(header, content):
	fd_header = open(header, "w")
	fd_header.write(content)
	fd_header.close()

def automatic_header(dir, header, tab_offset):
	dir_data = read_dir(dir)
	res = format_dir_datas(dir_data, tab_offset)
	header_content = create_header(header, res)
	# print(header_content)
	write_header(header, header_content)

automatic_header("./srcs/lexer", 			"./includes/sh_lexer.h", 5)
automatic_header("./srcs/expansions",		"./includes/sh_expansions.h", 0)
automatic_header("./srcs/traverse_tools",	"./includes/sh_traverse_tools.h", 0)
automatic_header("./srcs/vars",				"./includes/sh_vars.h", 0)
automatic_header("./srcs/traverse",			"./includes/sh_traverse.h", 0)
automatic_header("./srcs/builtin",			"./includes/sh_builtin.h", 0)
automatic_header("./srcs/exec",				"./includes/sh_exec.h", 5)
automatic_header("./srcs/perror",			"./includes/sh_perror.h", 0)
automatic_header("./srcs/grammar",		"./includes/sh_grammar.h", 5)
automatic_header("./srcs/parser/productions","./includes/sh_productions.h", 0)
automatic_header("./srcs/parser",			"./includes/sh_parser.h", 5)
automatic_header("./srcs/command_line", "./includes/sh_command_line.h", 5)
automatic_header("./srcs/command_line/autocomplete", "./includes/sh_autocompletion.h", 5)
automatic_header("./srcs/",			"./includes/sh_21.h", 5)
######automatic_header("./srcs/parser", "./includes/sh_tokens.h", 0)



# automatic_header("./test", "./header.h", 0)

