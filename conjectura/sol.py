n=196

def is_pal(n):
	return str(n) == str(n)[::-1]

x = 0
while not is_pal(n):
	n += int(str(n)[::-1])
	x += 1
	if x == 10: break
print len(str(n))
print x
