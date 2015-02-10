"""Printeaza
<numarul> <in_cate_operatii_se_face> <lungimea_lui_la_final>
"""

stream = open('numere.txt', 'w')

max_iteratii = 1000

def is_pal(n):
	return str(n) == str(n)[::-1]

for i in range(1, 10000):
  if i%1000 == 0: print(i)
  n = i
  if is_pal(n):
    stream.write("{0} {1} {2}\n".format(i, 0, len(str(i))))
    continue
  x = 0
  while not is_pal(n):
  	n += int(str(n)[::-1])
  	x += 1
  	if x == max_iteratii: break
  if is_pal(n):
    stream.write("{0} {1} {2}\n".format(i, x, len(str(n))))
  else:
    stream.write("{0} -1 {2}\n".format(i, x, len(str(n))))
