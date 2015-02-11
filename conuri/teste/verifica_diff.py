from sh import cp, rm, diff, ErrorReturnCode
import sh
import os

SURSA_VERIFICATA = 'cilindri-robert.cpp'

cp('../' + SURSA_VERIFICATA, '.')
os.system('g++ ' + SURSA_VERIFICATA)

filename = 'conuri'
for i in range(0, 10):
  if (i == 2):
    continue
  print 'Testul ', i
  cp(str(i) + '-' + filename + '.in', 'conuri.in')
  os.system('./a.out')
  print diff('conuri.out', str(i) + '-' + filename + '.ok', _ok_code=[0, 1])

for extension in ['in', 'out']:
  rm('conjectura.' + extension)
rm(SURSA_VERIFICATA)
rm('a.out')
