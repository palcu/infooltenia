from sh import cp, rm
import sh
import os

cp('../conjectura-palcu.cpp', '.')
os.system('g++ conjectura-palcu.cpp')

filename = 'grader_test'
for i in range(1, 10):
  print 'Testul ', i
  cp(filename + str(i) + '.in', 'conjectura.in')
  os.system('./a.out')
  cp('conjectura.out', filename + str(i) + '.ok')

for extension in ['in', 'out']:
  rm('conjectura.' + extension)
rm('conjectura-palcu.cpp')
rm('a.out')
