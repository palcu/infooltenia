from sh import cp, rm
import sh
import os

SURSA_CPP = 'lipsa_palcu.cpp'

cp('../' + SURSA_CPP, '.')
os.system('g++ ' + SURSA_CPP)

filename = 'grader_test'
for i in range(1, 11):
  print 'Testul ', i
  cp(filename + str(i) + '.in', 'lipsa.in')
  os.system('./a.out')
  cp('lipsa.out', filename + str(i) + '.ok')

for extension in ['in', 'out']:
  rm('lipsa.' + extension)
rm(SURSA_CPP)
rm('a.out')
