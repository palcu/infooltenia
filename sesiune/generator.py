from random import randint, shuffle

N = 6

v = [randint(1, N) for _ in range(4)]
S = sum(v)

print N, S
for _ in range(N-4):
  v.append(randint(1, N))
shuffle(v)

for _ in v:
  print _,
