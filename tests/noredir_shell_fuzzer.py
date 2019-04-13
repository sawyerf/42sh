#!/usr/bin/python3

import random
import string
import tempfile
import os
import shutil

g_max_fd = 3


g_tokens = ['"', '\'', '$', '\\', '']
g_redir = ['>', '<']
g_aggreg = ['>&', '<&']
tmpdir = tempfile.mkdtemp()
g_redir_pre = tmpdir + "/" 
sep = [';']
g_op = ["&&", "||"]
wspace = ['\n', ' ']

#word += random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits)

g_var_list = []

random.seed

def random_n_str(n):
    return ''.join(random.choice(string.ascii_uppercase + string.ascii_lowercase + string.digits) for _ in range(n))

def insert_word(maxlen, addvar):  
    rand_s =  random_n_str(random.randint(1, maxlen))
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
        elif (rand == 8):
            word += '\\'
        elif (rand < 20) and (addvar == True):
            word += '$' + random.choice(g_var_list)
        word += c
    if (in_sq == 1):
        word = word + "'"
    if (in_dq == 1):
        word = word + '"'
    return word 

def insert_redir():
    r = random.randint(0, 10)
    if (r < 5):
        redir = str(random.randint(0, g_max_fd)) + random.choice(g_redir) + g_redir_pre + random_n_str(random.randint(1, 6))
    else:# (r >= 5) && (r < 7):
        redir = str(random.randint(0, 255)) + random.choice(g_aggreg) + str(random.randint(1, g_max_fd))
    return redir 

def insert_assign(attach):
        var_name = random_n_str(random.randint(1, 6))
        if (var_name[0].isdigit()):
            var_name = random.choice(string.ascii_uppercase + string.ascii_lowercase) + var_name
        if (attach == True):
          g_var_list.append(var_name)
        assign = var_name + "=" + insert_word(50, False)# random_n_str(random.randint(1, 12))
        return assign 

def generate_prefix():
    pre = " "
    if (random.randint(1,3) == 2):
        pre = pre #+ insert_redir()
    else:
        pre = pre + insert_assign(False)
    return pre

def generate_suffix():
    suf = " "
    if (random.randint(1,3) == 2):
        suf = suf #+  insert_redir()
    else:
        suf = suf +  insert_word(25, True)
    return suf

def create_simple_cmd(line):
    while (random.randint(1,7) != 1):
            line = line  + generate_prefix()
    line = line + " " + "echo"
    while (random.randint(1,7) != 1):
        line = line + " " + generate_suffix()
    return line

def generate_pipeline():
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

def generate_var_only():
    var_only = ""
    i = 0
    while i != 2:
        var_only += " " + insert_assign(True)
        i = random.randint(1, 24)
    return var_only

def generate_cmdline():
    line = ""
    line += generate_var_only() + " ; "
    line += generate_and_or()
    rand = 0;
    while (rand != 2):
        line += generate_and_or() + " " +  generate_sep()
        rand = random.randint(1, 6)
    return line


print(generate_cmdline())
#print('======================================================')
#print(g_var_list)
#print('==========')
#print(tmpdir)
shutil.rmtree(tmpdir)
