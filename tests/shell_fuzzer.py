#!/usr/bin/python3

import random
import string

g_max_fd = 3


g_tokens = ['"', '\'', '$', '\\', '']

g_redir = ['>', '<', '>&', '<&']


sep = [';']

g_op = ["&&", "||"]

random.seed

wspace = ['\n', ' ']

#word += random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits)

def	random_n_str(n):
	return ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range(n))

def insert_word():	
	rand_s =  " " + random_n_str(random.randint(1, 6))
	in_sq = -1;
	in_dq = -1;
	rand = 0;
	word = ''
	for c in rand_s:
		rand = random.randint(1, 25)
		if (rand == 5):
			word += '\''
			if (in_dq == -1):
				in_sq = -in_sq
		elif (rand == 6):
			word += '"'
			if (in_sq == -1):
				in_dq = -in_dq
		elif (rand == 7):
			word += '$'
		elif (rand == 8):
			word += '\\'
		word += c
	if (in_sq == 1):
		word = word + "'"
	if (in_dq == 1):
		word = word + '"'
	return word 

def insert_redir():
	redir = str(random.randint(0, g_max_fd)) + random.choice(g_redir) + random_n_str(random.randint(1, 6))
	return redir 

def insert_assign():
	assign = random_n_str(random.randint(1, 6)) + "=" + random_n_str(random.randint(1, 12))
	return assign 

def	generate_prefix():
	pre = " "
	if (random.randint(1,3) == 2):
		pre = pre + insert_redir()
	else:
		pre = pre + insert_assign()
	return pre

def	generate_suffix():
	suf = " "
	if (random.randint(1,3) == 2):
		suf = suf +  insert_redir()
	else:
		suf = suf +  insert_word()
	return suf

def create_simple_cmd(line):
	while (random.randint(1,7) != 1):	
		line = line  + generate_prefix()	
	line = line + " " + insert_word()
	while (random.randint(1,7) != 1):
		line = line + " " + generate_suffix()	
	return line

def	generate_pipeline():
	line = ""
	rand = 0;
	line = create_simple_cmd(line)
	while (rand != 2):
		line += " | " + random.choice(wspace) + create_simple_cmd("")
		rand = random.randint(1, 6)
	return line

def generate_and_or():
	line = ""
	line = generate_pipeline()
	rand = 0;
	while (rand != 2):
		line += " " + random.choice(g_op) + " " + generate_pipeline()
		rand = random.randint(1, 6)
	return line


def generate_sep():
	line = ""
	rand = 0
	line += random.choice(sep);
	while (rand != 2):
		line += random.choice(wspace)
		rand = random.randint(1, 6)
	return line

def generate_cmdline():
	line = ""
	line += generate_and_or()
	rand = 0;
	while (rand != 2):
		line += generate_and_or() + " " +  generate_sep()
		rand = random.randint(1, 6)
	return line


print(generate_cmdline())
