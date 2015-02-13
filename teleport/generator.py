from random import randint

N = 100
MAX_ITEM_ARRAY = min(100, N)
nCheats = randint(1, 11)
cheatSize = randint(2, MAX_ITEM_ARRAY + 1)

print N, nCheats, cheatSize

for i in range(N):
  print randint(1, MAX_ITEM_ARRAY + 1),
