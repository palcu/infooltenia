from random import randint, shuffle

N = 1000
MAX_S = 1000000

v = [randint(1000, 100000) for _ in range(4)]
S = sum(v)

while len(v)<N:
  v.append(randint(1, 100))
v.pop()
shuffle(v)

print len(v), S
for _ in v:
  print _,
