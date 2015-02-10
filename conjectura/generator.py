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

n = 10
print(n)

shuffle(numere)
i = 0
for x in numere:
  if x['length'] < MAX_LEN_INT and x['id'] < 1000:
    print x['id']
    i += 1
  if i == n: break
