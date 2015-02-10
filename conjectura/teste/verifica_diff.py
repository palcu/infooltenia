from sh import cp, rm, diff, ErrorReturnCode
import sh
import os

SURSA_VERIFICATA = 'conjectura-inturi.cpp'

cp('../' + SURSA_VERIFICATA, '.')
os.system('g++ ' + SURSA_VERIFICATA)

filename = 'grader_test'
for i in range(1, 11):
  print 'Testul ', i
  cp(filename + str(i) + '.in', 'conjectura.in')
  os.system('./a.out')
  print diff('conjectura.out', filename + str(i) + '.ok', _ok_code=[0, 1])

for extension in ['in', 'out']:
  rm('conjectura.' + extension)
rm(SURSA_VERIFICATA)
rm('a.out')
