from random import shuffle


stream = open('numere.txt')
numere = []
for line in stream:
  elements = line.split()
  numere.append({'id': int(elements[0]),
                 'iterations': int(elements[1]),
                 'length': int(elements[2])})

MAX_INT = 2147483647
MAX_LEN_INT = len(str(MAX_INT)) - 1

n = 100
print(n)

numere.sort(key=lambda x: x['length'], reverse=True)
for x in numere[:n]:
  print x['id']
