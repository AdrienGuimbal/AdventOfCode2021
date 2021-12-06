input ← ⍎¨','(≠⊆⊢)⊃⊃⎕NGET'/home/adri/Programs/adventOfCode2021/Day6/input.txt' 1

generations ← (≢(({((⍵-1)~-1),((+/(0=⍵))/(8 6))}⍣80)⊢))

⍝ generations ← {≢({((⍵-1)~-1),((+/(0=⍵))/(8 6))}⍣⍺)}

⍝ itt ← {((⍵-1)~-1),((+/(0=⍵))/(8 6))}

