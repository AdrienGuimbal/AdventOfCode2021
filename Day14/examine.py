import sys
string = sys.argv[1]
dico = {}
for i in range(len(string)-1):
    if string[i]+string[i+1] in dico.keys():
        dico[ string[i]+string[i+1] ] +=1
    else :
        dico[ string[i]+string[i+1] ] = 1
for k in sorted(dico.keys()):
    print(f"{k} : {dico[k]}")
