from random import randint
import sys

N = int(sys.argv[1])
MAX_ITEM_ARRAY = min(100, N)
nCheats = randint(0, 3)
cheatSize = randint(2, MAX_ITEM_ARRAY + 1)

print N, nCheats, cheatSize

v = []
for i in range(N):
  v.append(str(randint(1, MAX_ITEM_ARRAY + 1)))

print " ".join(v)
