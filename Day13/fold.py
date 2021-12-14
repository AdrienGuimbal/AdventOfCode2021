import matplotlib.pyplot as plt
#file = open("input_test.txt", 'rt')
file = open("input.txt", 'rt')

points = set()
folds = []

for line in file:
	if len(line) < 2:
		pass
	elif line.startswith("fold") :
		folds.append((line[11], int(line.strip()[13:])))
	else :
		points.add(tuple(int(x) for x in line.strip().split(',')))

# print(points)
# print(folds)

def show_sheet(sheet):
	plt.scatter([i[0] for i in sheet], [-i[1] for i in sheet])
	plt.show()

first = True
for axe, nb in folds:
	if first:
		print("Problème 1 :", len(points))
		first = False
	#print("fold", axe, nb)
	if axe == 'x':
		points = set([(nb - abs(x - nb), y) for x, y in points])
	if axe == 'y':
		points = set([(x, nb - abs(y - nb)) for x, y in points])
show_sheet(points)
