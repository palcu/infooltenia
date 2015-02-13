from sh import cp, rm, diff, ErrorReturnCode
import sh
import os

SURSA_VERIFICATA = 'sesiune-N2logN.cpp'

cp('../' + SURSA_VERIFICATA, '.')
os.system('g++ ' + SURSA_VERIFICATA + ' -O3')

filename = 'grader_test'
for i in range(1, 11):
  print 'Testul ', i
  cp(filename + str(i) + '.in', 'sesiune.in')
  os.system('time ./a.out')
  print diff('sesiune.out', filename + str(i) + '.ok', _ok_code=[0, 1])

for extension in ['in', 'out']:
  rm('sesiune.' + extension)
rm(SURSA_VERIFICATA)
rm('a.out')
