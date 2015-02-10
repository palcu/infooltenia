from random import shuffle, randint


stream = open('numere.txt')
numere = []
for line in stream:
  elements = line.split()
  numere.append({'id': int(elements[0]),
                 'iterations': int(elements[1]),
                 'length': int(elements[2])})

MAX_INT = 2147483647
MAX_LEN_INT = len(str(MAX_INT)) - 1

n = 20
print(n)

shuffle(numere)
for x in numere[:n-1]:
  print x['id']

numere.sort(key=lambda x: x['length'], reverse=True)
print numere[randint(1, 100)]['id']
