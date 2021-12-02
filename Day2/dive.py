f = open("input.txt", 'rt')

# ploblem 1
horiz1 = depth1 = 0

# problem 2
aim = horiz2 = depth2 = 0

while True:
	st=f.readline()
	if st=='' : break

	direc, nb = st.split() # get numbers
	nb = int(nb)
	
	# to replace with a match when 3.10 will be avaliable
	if direc=="forward":
		horiz1+=nb
		horiz2+=nb
		depth2+=aim*nb
	elif direc=="down":
		depth1+=nb
		aim   +=nb
	elif direc=="up":
		depth1-=nb
		aim   -=nb

print("Résultat pb1 :",horiz1*depth1)
print("Résultat pb2 :",horiz2*depth2)
f.close()