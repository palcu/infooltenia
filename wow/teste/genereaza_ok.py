from sh import cp, rm
import sh
import os

cp('../wow-100.cpp', '.')
os.system('g++ wow-100.cpp')

filename = 'grader_test'
for i in range(1, 4):
  print 'Testul ', i
  cp(filename + str(i) + '.in', 'wow.in')
  os.system('./a.out')
  cp('wow.out', filename + str(i) + '.ok')

for extension in ['in', 'out']:
  rm('wow.' + extension)
rm('wow-100.cpp')
rm('a.out')
