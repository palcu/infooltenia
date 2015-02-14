from sh import cp, rm
import sh
import os

cp('../tel_and.cpp', '.')
os.system('g++ tel_and.cpp')

filename = 'grader_test'
for i in range(1, 11):
  print 'Testul ', i
  cp(filename + str(i) + '.in', 'teleport.in')
  os.system('./a.out')
  cp('teleport.out', filename + str(i) + '.ok')

for extension in ['in', 'out']:
  rm('teleport.' + extension)
rm('tel_and.cpp')
rm('a.out')
