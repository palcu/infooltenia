from random import randint

N = 10000
MAX_ITEM_ARRAY = min(100, N)
nCheats = randint(0, 3)
cheatSize = randint(2, MAX_ITEM_ARRAY + 1)

print N, nCheats, cheatSize

for i in range(N):
  print randint(1, MAX_ITEM_ARRAY + 1),
