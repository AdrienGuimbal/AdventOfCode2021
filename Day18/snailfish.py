from typing import List, Union

def printnum(num):
	for curr, nxt in zip(num[:-1], num[1:]):
		if type(curr) == int or type(nxt) == int:
			print(curr, end=" ")
		else:
			print(curr, end="")
	print(num[-1],end="\n")

def is_reduced(x):
	nesting = 0
	for e in x:
		if   e == "," : pass
		elif e == "[" : nesting += 1
		elif e == "]" : nesting -= 1
		elif e > 9    : return False
		
		if nesting > 4: return False
	assert(nesting == 0)
	return True

def reduce (num : list) -> None:
	num = num[:]
	nesting = 0
	for i, c in enumerate(num):
		if c == "[" : nesting += 1
		if c == "]" : nesting -= 1

		# explodes
		if nesting > 4:
			try :
				assert(num.pop(i+3) == "]")
				right = num.pop(i+2)
				left  = num.pop(i+1)
				assert(num.pop(i) == "[")
			except BaseException as err:
				printnum(num[i:i+4])
				raise err
			num.insert(i, 0)

			# add to left
			j = i
			while j > 0 :
				j -= 1
				if type(num[j]) == int:
					num[j] += left
					j = -1
			# add to right
			j = i
			while j < len(num) -1:
				j += 1
				if type(num[j]) == int:
					num[j] += right
					j = len(num)
			return num
	
	for i, c in enumerate(num):
		if type(c) == int and c >= 10:
			nb = num.pop(i)
			num.insert(i, "]")
			num.insert(i, (nb + 1)//2)
			num.insert(i,  nb//2)
			num.insert(i, "[")
			return num
	return num

def add (x, y) -> list:
	res = ["["] + x[:] + y[:] + ["]"]
	#printnum(res)
	while not is_reduced(res):
		res = reduce(res)
	#	printnum(res)
	return res

def _magnitude (expr) :
		if type(expr) == int :
			return expr
		else :
			return 3*_magnitude(expr[0]) + 2*_magnitude(expr[1])
def magnitude (num : list):
	revirguled = ""
	for i, elt in enumerate(num):
		revirguled += str(elt)
		#if type(elt) == int or (elt == "]" and (revirguled[i+1] == "[" or type(revirguled[i+1]) == int)):
		if i == 0 or i == len(num) - 1 : continue
		if (elt == "]" or type(elt) == int) and num[i+1] != "]" :
			revirguled += ","
	#print(eval(revirguled))
	return _magnitude(eval(revirguled))

############
#   MAIN   #
############

#input_file = open("input_test.txt", "rt")
input_file = open("input.txt", "rt")

def parse(line):
	res = []
	for char in line.strip():
		if char.isnumeric():
			res.append(int(char))
		elif char != ",":
			res.append(char)
	return res

numbers = []
for line in input_file :
	numbers.append(parse(line))

res = numbers[0]
printnum(res)
for num in numbers[1:]:
	res = add(res, num)

print("Résultat pb1 :", magnitude(res))

magnitudes = []
for x in numbers:
	for y in numbers:
		magnitudes.append(magnitude(add(x,y)))
		magnitudes.append(magnitude(add(y,x)))
print("Résultat pb1 :", max(magnitudes))