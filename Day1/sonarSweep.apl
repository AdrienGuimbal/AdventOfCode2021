⍝ dump input file input in "input" 
input ← ⎕NGET'/home/adri/Programs/adventOfCode2021/Day1/input_apl.txt'

⍝ solution function
⍝sol ← {+/(¯1↓(1⌽⍵)>⍵)}

sol ← {+/2</⍵}
sol2 ← {+/2</3+/⍵}

sol input
sol2 input