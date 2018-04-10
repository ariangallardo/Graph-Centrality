import matplotlib.pyplot as plt

x = []
y = []

i = 1000

while (i <= 100000):
	x.append(i)
	t = (float)(input())
	y.append(t)
	print(t)
	i+=1000

plt.plot(x,y,"bh")
plt.show()
