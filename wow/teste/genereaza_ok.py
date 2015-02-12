from sh import cp, rm
import sh
import os

cp('../wow-palcu.cpp', '.')
os.system('g++ wow-palcu.cpp')

filename = 'grader_test'
for i in range(1, 11):
  print 'Testul ', i
  cp(filename + str(i) + '.in', 'wow.in')
  os.system('./a.out')
  cp('wow.out', filename + str(i) + '.ok')

for extension in ['in', 'out']:
  rm('wow.' + extension)
rm('wow-palcu.cpp')
rm('a.out')
