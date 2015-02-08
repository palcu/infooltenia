n=231439995

def is_pal(n):
	return str(n) == str(n)[::-1]

x = 0
while not is_pal(n):
	n += int(str(n)[::-1])
	x += 1
print len(str(n))
print x