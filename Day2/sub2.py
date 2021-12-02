f = open("input.txt", 'rt')
st = 'zerz'

fd = d = 0
while st!='':
	st=f.readline()
	direc, nb = st.split()
	if direc=="forward":
		fd+=int(nb)
	if direc=="down":
		d+=int(nb)
	if direc=="up":
		d-=int(nb)
	print(fd*d)
