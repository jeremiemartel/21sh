#!/usr/bin/python3
fd = open("inc")
line = fd.readline()
while (line != ""):
	if (line[0] == '\t'):
		line = fd.readline()
		continue
	tab = line.split("\t")
	# print(tab)
	line = tab[len(tab) - 1]
	line = line.strip("\n;*")
	tab = line.split("(")
	line = tab[0]
	print(line)
	line = fd.readline()
