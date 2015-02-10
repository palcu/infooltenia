from sh import cp
import sh

cp('../conjectura-palcu.cpp', '.')
sh.Command('g++ conjectura-palcu.cpp')

filename = 'grader_test'
for i in range(1, 10):
  cp(filename + str(i) + '.in', 'convertor.in')
  sh.Command('./a.out')
  cp('convertor.out', filename + str(i) + '.ok')
