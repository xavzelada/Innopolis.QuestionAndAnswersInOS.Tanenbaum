import random

n = 1000
disc_size = 200

with open("input.txt", "w") as f:
	print(n, end="\n", file=f)
	for i in range(0, n):
		print(random.randint(0, disc_size - 1), end="\n", file=f)
