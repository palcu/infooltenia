from random import shuffle


n = 10
m = 2
print("{0} {1}".format(n, m))

for i in range(m):
  v = range(1, n+1)
  shuffle(v)
  print(" ".join([str(x) for x in v[1:]]))
