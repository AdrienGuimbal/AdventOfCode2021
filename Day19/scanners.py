#%%
from os import environ
from typing import Set, Dict, List, Tuple, Union
#%%%%%%%%%%%%%%%%%#
#    GET INPUT    #
###################

file_input = open("input.txt", "rt")
NB_FOR_COMPATIBLE = 12

#file_input = open("input_test.txt", "rt")
#NB_FOR_COMPATIBLE = 4

scanners = []
for line in file_input:
	#print(line.strip())
	if line.strip() == "":
		continue
	elif line.startswith("---") :
		#print("NEW SCAN")
		scanners.append(set())
		continue
	else :
		scanners[-1].add(tuple(int(x) for x in line.strip().split(',')))

file_input.close()
del file_input, line

#%%%%%%%%%%%%%%%%#
#    FONTIONS    #
##################
# rot_2 = lambda scan : {( x, -y, -z) for x, y, z in scan} # legacy
# [T, rot_Z(T), rot_Z(rot_Z(T)), rot_Z(rot_Z(rot_Z(T))),\
# B, rot_Z(B), rot_Z(rot_Z(B)), rot_Z(rot_Z(rot_Z(B))),\
# F, rot_X(F), rot_X(rot_X(F)), rot_X(rot_X(rot_X(F))),\
# K, rot_X(K), rot_X(rot_X(K)), rot_X(rot_X(rot_X(K))),\
# L, rot_Y(L), rot_Y(rot_Y(L)), rot_Y(rot_Y(rot_Y(L))),\
# R, rot_Y(R), rot_Y(rot_Y(R)), rot_Y(rot_Y(rot_Y(R)))]
# pb with 8-rev, 17-rev, 21-rev

rot_X = lambda scan : {( x, -z,  y) for x, y, z in scan}
rot_Y = lambda scan : {( z,  y, -x) for x, y, z in scan}
rot_Z = lambda scan : {(-y,  x,  z) for x, y, z in scan}


rot_2X = lambda scan : {( x, -y, -z) for x, y, z in scan}
rot_2Y = lambda scan : {(-x,  y, -z) for x, y, z in scan}
rot_2Z = lambda scan : {(-x, -y,  z) for x, y, z in scan}


def get_rotations(scan):
	T = scan         # z pointing Top
	B = rot_2Y(T)    # z pointing Bottom
	F = rot_Y(scan)  # z pointing Front
	K = rot_2Z(F)    # z pointing bacK
	R = rot_X(scan)  # z pointing Right
	L = rot_2X(R)    # z pointing Left
	return [T, rot_Z(T), rot_2Z(T), rot_Z(rot_2Z(T)),\
			B, rot_Z(B), rot_2Z(B), rot_Z(rot_2Z(B)),\
			F, rot_X(F), rot_2X(F), rot_X(rot_2X(F)),\
			K, rot_X(K), rot_2X(K), rot_X(rot_2X(K)),\
			L, rot_Y(L), rot_2Y(L), rot_Y(rot_2Y(L)),\
			R, rot_Y(R), rot_2Y(R), rot_Y(rot_2Y(R))]

def are_compatible(delta1 : Set[Tuple[int]], delta2 : Set[Tuple[int]]) -> bool:
	inter = len(delta1.intersection(delta2))
	#if inter>1 and inter<NB_FOR_COMPATIBLE: print("partial match",inter, "in common")
	return inter >= NB_FOR_COMPATIBLE

def get_deltas(ref : Tuple[int], scan : Set[Tuple[int]]) -> Set[Tuple[int]]:
	X, Y, Z = ref
	return set((x-X, y-Y, z-Z) for x, y, z in scan)

def get_tranformated(scan1 : Set[Tuple[int]], scan2 : Set[Tuple[int]]):
	for s1 in scan1:
		delta1 = get_deltas(s1, scan1)
		for n_rot, rscan2 in enumerate(get_rotations(scan2)):
			for s2 in rscan2:
				delta2 = get_deltas(s2, rscan2)
				if are_compatible(delta1, delta2):
					print(f"worked whith rotation n°{n_rot}")
					x0, y0, z0 = s1
					return {(x0+dx, y0+dy, z0+dz) for dx, dy, dz in delta2},\
						(s1[0]-s2[0], s1[1]-s2[1], s1[2]-s2[2])
	return set(), (0,0,0)
	


##################
#      MAIN      #
##################
main_scan = scanners[0].copy()
scanners_coord = [(0,0,0)]
done = set([0])
changes = True
while changes:
	changes = False
	for index, scan in enumerate(scanners):
		if not index in done:
			res, scan_coord = get_tranformated(main_scan, scan)
			if len(res) > 0:
				print(f"- scan {index} matched")
				changes = True
				done.add(index)
				main_scan = main_scan.union(res)
				scanners_coord.append(scan_coord)
			else :
				print(f"scan {index} not matching")
print(set(range(len(scanners))).symmetric_difference(done) ,"n'ont pas marché")
print("Résultat pb1 :", len(main_scan))

# %%
manhattan_dist = lambda s1, s2 : abs(s1[0]-s2[0]) + abs(s1[1]-s2[1]) + abs(s1[2]-s2[2])
max_distance = -1
for i, s1 in enumerate(scanners_coord):
	for j, s2 in enumerate(scanners_coord[i+1:]):
		max_distance = max(manhattan_dist(s1, s2), max_distance)
print("Résultat pb2 :", max_distance)
# %%
