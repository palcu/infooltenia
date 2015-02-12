from sh import cp, rm, diff, ErrorReturnCode
import sh
import os

SURSA_VERIFICATA = 'lipsa_n_patrat.cpp'

cp('../' + SURSA_VERIFICATA, '.')
os.system('g++ ' + SURSA_VERIFICATA)

filename = 'grader_test'
for i in range(1, 11):
  print 'Testul ', i
  cp(filename + str(i) + '.in', 'lipsa.in')
  os.system('./a.out')
  print diff('lipsa.out', filename + str(i) + '.ok', _ok_code=[0, 1])

for extension in ['in', 'out']:
  rm('lipsa.' + extension)
rm(SURSA_VERIFICATA)
rm('a.out')
