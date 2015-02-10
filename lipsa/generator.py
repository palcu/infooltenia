from random import shuffle


n = 8000
m = 90
print("{0} {1}".format(n, m))

to_remove = range(1, n+1)
for i in range(m):
  v = range(1, n+1)
  shuffle(v)
  x = to_remove.pop()
  v.remove(x)
  print(" ".join([str(x) for x in v]))
