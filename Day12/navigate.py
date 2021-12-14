from typing import Dict, Set


# file = """dc-end
# HN-start
# start-kj
# dc-start
# dc-HN
# LN-dc
# HN-end
# kj-sa
# kj-HN
# kj-dc""".splitlines()

file = open("input.txt", 'rt')
inp = [line.strip().split('-') for line in file]
file.close()

net : Dict[str, Set[str]] = {}

for cave1, cave2 in inp:
	if cave1 in net.keys():
		net[cave1].add(cave2)
	else :
		net[cave1] = set([cave2])
	if cave2 in net.keys():
		net[cave2].add(cave1)
	else :
		net[cave2] = set([cave1])

def chemin(past, curent):
	if curent == "end" :
		return 1
	ch = 0
	for cave in net[curent]:
		if cave[0] < 'a' or (not cave in past) :
			ch += chemin(past+[curent], cave)
	return ch

res1 = sum(chemin(["start"], cave) for cave in net["start"])

print("Problème 1:", res1)

paths = set()
def chemin2(past, twice, curent):
	if curent == "end" :
		##print(str(past+[curent]))
		paths.add("-".join(past+[curent]))
		return
	for cave in net[curent]:
		if cave == "start":
			pass
		elif cave[0] < 'a':
			chemin2(past+[curent], twice, cave)
		elif cave in past and not twice:
			chemin2(past+[curent], True, cave)
		elif not cave in past :
			chemin2(past+[curent], twice, cave)

for cave in net["start"]:
	chemin2(["start"], False, cave)

#for i in paths : print(i)

print("Problème 2 :", len(paths))